#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#define ERROR_ALLOCATION_FAILED 1
#define ERROR_INVALID_INPUT 2
#define ERROR_FILE_OPERATION 3
#define ERROR_NULL_POINTER 4

/*
Struct that represents a neuron in a neural network.
*/
typedef struct{
    double* weights;
    double bias;
    double activation;
    double delta; // Error delta for backprogagation
    size_t num_weights; // Number of weights(connections from previos layers)
} Neuron;

/*
Struct to represent a layer in a neural network.
*/
typedef struct{
    Neuron* neurons; // Array of neurons
    size_t num_neurons; // Number of neurons in the layer
} Layer;

/*
Struct to represent a neural network.
*/
typedef struct {
    Layer* layers; // Array of layers
    size_t num_layers; // Number of layers in the network
    size_t* layer_sizes; // Size of each layer
    double learning_rate; // Learning rate for training
} NeuralNetwork;

NeuralNetwork* create_neuronal_nertwork(const size_t* layer_sizes, size_t num_layers, double learing_rate) {
    // Validate input parameters
    if (layer_sizes == NULL || num_layers < 2) {
        fprintf(stderr, "Error: Invalid input parameters.\n");
        return NULL;
    }

    /* Allocate memoery for the neuronal network */
    NeuralNetwork* network = (NeuralNetwork*)calloc(1, sizeof(NeuralNetwork));
    if (network == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    /* Initialize network parameters */
    network->num_layers = num_layers;
    network->learning_rate = learing_rate;

    /* Allocate memory for layer sizes */
    network->layers = (Layer*)calloc(num_layers, sizeof(Layer));
    if (network->layers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(network->layers);
        free(network);
        return NULL;
    }

    network->layer_sizes = (size_t*)calloc(num_layers, sizeof(size_t));
    if (network->layer_sizes == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(network->layer_sizes);
        free(network->layers);
        free(network);
        return NULL;
    }

}


int main() {

    return 0;
}