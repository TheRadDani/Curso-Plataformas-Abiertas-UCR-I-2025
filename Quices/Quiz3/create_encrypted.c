#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float valor;
    char timestamp[20];
} Sensor;

void encrypt_file(const char *input_filename, const char *output_filename, unsigned char key) {
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
    Sensor sensor = {1, 25.5f, "2023-10-25 12:00:00"};
    
    // Guardar estructura en archivo temporal sin encriptar
    FILE *temp = fopen("temp.bin", "wb");
    fwrite(&sensor, sizeof(Sensor), 1, temp);
    fclose(temp);

    // Encriptar el archivo con XOR (clave 0xAB)
    encrypt_file("temp.bin", "sensor_encrypted.bin", 0xAB);
    remove("temp.bin"); // Eliminar temporal

    return 0;
}