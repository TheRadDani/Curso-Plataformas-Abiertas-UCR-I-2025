
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float valor;
    char timestamp[20];
    float temperatura; // Nuevo atributo
} SensorUpdated;

void xor_crypt(const char *input_filename, const char *output_filename, unsigned char key) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(1);
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        fputc(c ^ key, output);
    }

    fclose(input);
    fclose(output);
}

int main() {
    unsigned char key = 0xAB;

    // Leer y descifrar archivo original
    xor_crypt("sensor_encrypted.bin", "temp_decrypted.bin", key);
    
    FILE *temp = fopen("temp_decrypted.bin", "rb");
    SensorUpdated sensor;
    fread(&sensor, sizeof(SensorUpdated) - sizeof(float), 1, temp); // Leer sin el nuevo campo
    fclose(temp);
    remove("temp_decrypted.bin");

    // Añadir temperatura
    sensor.temperatura = 30.0f;

    // Guardar estructura actualizada temporalmente
    temp = fopen("temp_updated.bin", "wb");
    fwrite(&sensor, sizeof(SensorUpdated), 1, temp);
    fclose(temp);

    // Encriptar y guardar
    xor_crypt("temp_updated.bin", "sensor_updated_encrypted.bin", key);
    remove("temp_updated.bin");

    // Verificación
    xor_crypt("sensor_updated_encrypted.bin", "temp_verification.bin", key);
    temp = fopen("temp_verification.bin", "rb");
    SensorUpdated sensor_verif;
    fread(&sensor_verif, sizeof(SensorUpdated), 1, temp);
    fclose(temp);
    remove("temp_verification.bin");

    printf("ID: %d\nValor: %.2f\nTimestamp: %s\nTemperatura: %.2f\n",
           sensor_verif.id, sensor_verif.valor, sensor_verif.timestamp, sensor_verif.temperatura);

    return 0;
}