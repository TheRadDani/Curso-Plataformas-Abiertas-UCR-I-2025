#include <stdio.h>
#include <stdlib.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    // Open JSON file
    FILE *file = fopen("src/data.json", "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read JSON file into buffer
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return EXIT_FAILURE;
    }
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    // Parse JSON
    json jsonData = json::parse(buffer);
    free(buffer);

    // Access JSON values
    printf("Name: %s\n", jsonData["name"].get<std::string>().c_str());
    printf("Age: %d\n", jsonData["age"].get<int>());
    printf("City: %s\n", jsonData["city"].get<std::string>().c_str());

    return 0;
}