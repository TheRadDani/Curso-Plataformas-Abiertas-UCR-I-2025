#include "pico/stdlib.h"
#include "model.h"

int main() {
    stdio_init_all();
    printf("Starting ONNX inference on Pico!\n");

    // TODO: Replace with actual ONNX parsing and inference logic
    // For now, print the model size as a placeholder
    printf("Model size: %d bytes\n", tiny_sine_model_onnx_len);

    while (1) {
        tight_loop_contents();
    }
    return 0;
}