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

    /* Copy Layer sizes */
    if(memcpy(network->layer_sizes, layer_sizes, num_layers * sizeof(size_t)) != network->layer_sizes) {
        fprintf(stderr, "Error: Memory copy failed.\n");
        free(network->layer_sizes);
        free(network->layers);
        free(network);
        return NULL;
    }

    /* Initialize each layer */
    for(size_t i=0; i<num_layers; i++) {
        /* Validate layer size */
        if(layer_sizes[i] == 0) {
            fprintf(stderr, "Error: Layer size cannot be zero.\n");
            /* Clean up already allocated memory */
            for(size_t j=0; j<i;j++) {
                for(size_t k=0; k < network->layers[j].num_neurons; k++) {
                    free(network->layers[j].neurons[k].weights);
                }
                free(network->layers[j].neurons);
            }
            free(network->layer_sizes);
            free(network->layers);
            free(network);
            return NULL;
        }

        /* Set number of neurons in this layer */
        network->layers[i].num_neurons = layer_sizes[i];

        /* Allocate memory for neurons */
        network->layers[i].neurons = (Neuron*)calloc(layer_sizes[i], sizeof(Neuron));
        if(network->layers[i].neurons == NULL){
            fprintf(stderr, "Error: Memory allocation failed.\n");
            /* Clean up already allocated memory */
            for(size_t j=0; j<i;j++) {
                for(size_t k=0; k < network->layers[j].num_neurons; k++) {
                    free(network->layers[j].neurons[k].weights);
                }
                free(network->layers[j].neurons);
            }
            free(network->layer_sizes);
            free(network->layers);
            free(network);
            return NULL;
        }
        
        /* Initialize weights and biases */
        for(size_t j=0; j < layer_sizes[i]; j++) {
            network->layers[i].neurons[j].bias = 0.0;
            network->layers[i].neurons[j].activation = 0.0;
            network->layers[i].neurons[j].delta = 0.0;

            /* First layer has no weight (input layer) */
            if(i==0) {
                network->layers[i].neurons[j].num_weights = 0;
                network->layers[i].neurons[j].weights = NULL;
                continue;
            }

            /* Allocate memory for weights */
            size_t num_weights = layer_sizes[i-1];
            network->layers[i].neurons[j].num_weights = num_weights;
            network->layers[i].neurons[j].weights = (double*)calloc(num_weights, sizeof(double));
            if(network->layers[i].neurons[j].weights == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                /* Clean up already allocated memory */
                for(size_t k=0; k < j; k++) {
                    free(network->layers[i].neurons[k].weights);
                }
                free(network->layers[i].neurons);
                for(size_t j=0; j<i;j++) {
                    for(size_t k=0; k < network->layers[j].num_neurons; k++) {
                        free(network->layers[j].neurons[k].weights);
                    }
                    free(network->layers[j].neurons);
                }
                free(network->layer_sizes);
                free(network->layers);
                free(network);
                return NULL;
            }

            /* Initialize weights to random values */
            for(size_t k=0; k < num_weights; k++) {
                network->layers[i].neurons[j].weights[k] = ((double)rand() / RAND_MAX) * 0.1 - 0.05; // Random value between -0.05 and 0.05
            }
        }
    }
    return network;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}




int main() {

    return 0;
}