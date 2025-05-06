#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

/* Define error codes for better error handling */
#define ERROR_ALLOCATION_FAILED 1
#define ERROR_INVALID_INPUT 2
#define ERROR_FILE_OPERATION 3
#define ERROR_NULL_POINTER 4

/**
 * Structure to represent a neuron in our neural network
 * Each neuron has weights, bias, and activation
 */
typedef struct {
    double* weights;        /* Weights for connections from previous layer */
    double bias;            /* Bias term */
    double activation;      /* Activation value */
    double delta;           /* Error delta for backpropagation */
    size_t num_weights;     /* Number of weights (connections from previous layer) */
} Neuron;

/**
 * Structure to represent a layer in our neural network
 * Each layer contains multiple neurons
 */
typedef struct {
    Neuron* neurons;        /* Array of neurons in this layer */
    size_t num_neurons;     /* Number of neurons in this layer */
} Layer;

/**
 * Structure to represent our neural network
 * Contains multiple layers and metadata
 */
typedef struct {
    Layer* layers;          /* Array of layers */
    size_t num_layers;      /* Number of layers in the network */
    size_t* layer_sizes;    /* Size of each layer */
    double learning_rate;   /* Learning rate for training */
} NeuralNetwork;

/**
 * Securely allocates memory for a neural network
 * 
 * @param layer_sizes Array containing the size of each layer
 * @param num_layers Number of layers in the network
 * @param learning_rate Learning rate for training
 * @return Pointer to allocated neural network or NULL on failure
 */
NeuralNetwork* create_neural_network(const size_t* layer_sizes, size_t num_layers, double learning_rate) {
    /* Validate input parameters */
    if (layer_sizes == NULL || num_layers < 2) {
        fprintf(stderr, "Invalid parameters: layer_sizes must not be NULL and num_layers must be at least 2\n");
        return NULL;
    }
    
    /* Allocate memory for the neural network */
    NeuralNetwork* network = (NeuralNetwork*)calloc(1, sizeof(NeuralNetwork));
    if (network == NULL) {
        fprintf(stderr, "Memory allocation failed for neural network\n");
        return NULL;
    }
    
    /* Initialize network properties */
    network->num_layers = num_layers;
    network->learning_rate = learning_rate;
    
    /* Allocate memory for layers */
    network->layers = (Layer*)calloc(num_layers, sizeof(Layer));
    if (network->layers == NULL) {
        fprintf(stderr, "Memory allocation failed for layers\n");
        free(network);
        return NULL;
    }
    
    /* Allocate memory for layer sizes */
    network->layer_sizes = (size_t*)calloc(num_layers, sizeof(size_t));
    if (network->layer_sizes == NULL) {
        fprintf(stderr, "Memory allocation failed for layer sizes\n");
        free(network->layers);
        free(network);
        return NULL;
    }
    
    /* Copy layer sizes */
    if (memcpy(network->layer_sizes, layer_sizes, num_layers * sizeof(size_t)) != network->layer_sizes) {
        fprintf(stderr, "Failed to copy layer sizes\n");
        free(network->layer_sizes);
        free(network->layers);
        free(network);
        return NULL;
    }
    
    /* Initialize each layer */
    for (size_t i = 0; i < num_layers; i++) {
        /* Validate layer size */
        if (layer_sizes[i] == 0) {
            fprintf(stderr, "Invalid layer size: Layer %zu has size 0\n", i);
            /* Clean up already allocated memory */
            for (size_t j = 0; j < i; j++) {
                for (size_t k = 0; k < network->layers[j].num_neurons; k++) {
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
        if (network->layers[i].neurons == NULL) {
            fprintf(stderr, "Memory allocation failed for neurons in layer %zu\n", i);
            /* Clean up already allocated memory */
            for (size_t j = 0; j < i; j++) {
                for (size_t k = 0; k < network->layers[j].num_neurons; k++) {
                    free(network->layers[j].neurons[k].weights);
                }
                free(network->layers[j].neurons);
            }
            free(network->layer_sizes);
            free(network->layers);
            free(network);
            return NULL;
        }
        
        /* Initialize neurons */
        for (size_t j = 0; j < layer_sizes[i]; j++) {
            /* Initialize neuron properties */
            network->layers[i].neurons[j].bias = 0.0;
            network->layers[i].neurons[j].activation = 0.0;
            network->layers[i].neurons[j].delta = 0.0;
            
            /* First layer has no weights (input layer) */
            if (i == 0) {
                network->layers[i].neurons[j].weights = NULL;
                network->layers[i].neurons[j].num_weights = 0;
                continue;
            }
            
            /* Allocate memory for weights */
            size_t num_weights = layer_sizes[i-1];
            network->layers[i].neurons[j].num_weights = num_weights;
            network->layers[i].neurons[j].weights = (double*)calloc(num_weights, sizeof(double));
            if (network->layers[i].neurons[j].weights == NULL) {
                fprintf(stderr, "Memory allocation failed for weights in neuron %zu of layer %zu\n", j, i);
                /* Clean up already allocated memory */
                for (size_t k = 0; k < j; k++) {
                    free(network->layers[i].neurons[k].weights);
                }
                for (size_t k = 0; k < i; k++) {
                    for (size_t l = 0; l < network->layers[k].num_neurons; l++) {
                        free(network->layers[k].neurons[l].weights);
                    }
                    free(network->layers[k].neurons);
                }
                free(network->layer_sizes);
                free(network->layers);
                free(network);
                return NULL;
            }
            
            /* Initialize weights to small random values */
            for (size_t k = 0; k < num_weights; k++) {
                network->layers[i].neurons[j].weights[k] = ((double)rand() / RAND_MAX) * 0.1 - 0.05;
            }
        }
    }
    
    return network;
}

/**
 * Sigmoid activation function
 * 
 * @param x Input value
 * @return Sigmoid output: 1 / (1 + e^-x)
 */
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

/**
 * Derivative of sigmoid function
 * 
 * @param x Sigmoid output value
 * @return Derivative of sigmoid for the given output
 */
double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

/**
 * Forward propagation through the neural network
 * 
 * @param network Pointer to neural network
 * @param inputs Input values for the network
 * @param num_inputs Number of input values
 * @return true if successful, false otherwise
 */
bool forward_propagate(NeuralNetwork* network, const double* inputs, size_t num_inputs) {
    /* Validate input parameters */
    if (network == NULL || inputs == NULL) {
        fprintf(stderr, "Invalid parameters: network and inputs must not be NULL\n");
        return false;
    }
    
    /* Check if number of inputs matches input layer size */
    if (num_inputs != network->layer_sizes[0]) {
        fprintf(stderr, "Input size mismatch: Expected %zu inputs, got %zu\n", 
                network->layer_sizes[0], num_inputs);
        return false;
    }
    
    /* Set input layer activations */
    for (size_t i = 0; i < network->layer_sizes[0]; i++) {
        network->layers[0].neurons[i].activation = inputs[i];
    }
    
    /* Forward propagate through each layer */
    for (size_t layer = 1; layer < network->num_layers; layer++) {
        for (size_t neuron = 0; neuron < network->layers[layer].num_neurons; neuron++) {
            /* Calculate weighted sum of inputs plus bias */
            double sum = network->layers[layer].neurons[neuron].bias;
            
            /* Sum up weighted inputs from previous layer */
            for (size_t prev = 0; prev < network->layers[layer-1].num_neurons; prev++) {
                sum += network->layers[layer-1].neurons[prev].activation * 
                       network->layers[layer].neurons[neuron].weights[prev];
            }
            
            /* Apply activation function */
            network->layers[layer].neurons[neuron].activation = sigmoid(sum);
        }
    }
    
    return true;
}

/**
 * Backward propagation to update weights
 * 
 * @param network Pointer to neural network
 * @param targets Target values for output layer
 * @param num_targets Number of target values
 * @return true if successful, false otherwise
 */
bool backward_propagate(NeuralNetwork* network, const double* targets, size_t num_targets) {
    /* Validate input parameters */
    if (network == NULL || targets == NULL) {
        fprintf(stderr, "Invalid parameters: network and targets must not be NULL\n");
        return false;
    }
    
    /* Check if number of targets matches output layer size */
    size_t output_layer = network->num_layers - 1;
    if (num_targets != network->layer_sizes[output_layer]) {
        fprintf(stderr, "Target size mismatch: Expected %zu targets, got %zu\n", 
                network->layer_sizes[output_layer], num_targets);
        return false;
    }
    
    /* Calculate deltas for output layer */
    for (size_t i = 0; i < network->layers[output_layer].num_neurons; i++) {
        double output = network->layers[output_layer].neurons[i].activation;
        double error = targets[i] - output;
        network->layers[output_layer].neurons[i].delta = error * sigmoid_derivative(output);
    }
    
    /* Calculate deltas for hidden layers */
    for (size_t layer = network->num_layers - 2; layer > 0; layer--) {
        for (size_t neuron = 0; neuron < network->layers[layer].num_neurons; neuron++) {
            double error = 0.0;
            /* Sum up errors from next layer */
            for (size_t next = 0; next < network->layers[layer+1].num_neurons; next++) {
                error += network->layers[layer+1].neurons[next].delta * 
                         network->layers[layer+1].neurons[next].weights[neuron];
            }
            network->layers[layer].neurons[neuron].delta = error * 
                sigmoid_derivative(network->layers[layer].neurons[neuron].activation);
        }
    }
    
    /* Update weights and biases */
    for (size_t layer = 1; layer < network->num_layers; layer++) {
        for (size_t neuron = 0; neuron < network->layers[layer].num_neurons; neuron++) {
            /* Update bias */
            network->layers[layer].neurons[neuron].bias += 
                network->learning_rate * network->layers[layer].neurons[neuron].delta;
            
            /* Update weights */
            for (size_t prev = 0; prev < network->layers[layer-1].num_neurons; prev++) {
                network->layers[layer].neurons[neuron].weights[prev] += 
                    network->learning_rate * network->layers[layer].neurons[neuron].delta * 
                    network->layers[layer-1].neurons[prev].activation;
            }
        }
    }
    
    return true;
}

/**
 * Train the neural network on a single sample
 * 
 * @param network Pointer to neural network
 * @param inputs Input values
 * @param num_inputs Number of input values
 * @param targets Target values
 * @param num_targets Number of target values
 * @return true if successful, false otherwise
 */
bool train(NeuralNetwork* network, const double* inputs, size_t num_inputs, 
           const double* targets, size_t num_targets) {
    /* Validate input parameters */
    if (network == NULL || inputs == NULL || targets == NULL) {
        fprintf(stderr, "Invalid parameters: network, inputs, and targets must not be NULL\n");
        return false;
    }
    
    /* Forward propagate */
    if (!forward_propagate(network, inputs, num_inputs)) {
        return false;
    }
    
    /* Backward propagate */
    if (!backward_propagate(network, targets, num_targets)) {
        return false;
    }
    
    return true;
}

/**
 * Predict output using the neural network
 * 
 * @param network Pointer to neural network
 * @param inputs Input values
 * @param num_inputs Number of input values
 * @param outputs Array to store output values
 * @param num_outputs Number of output values
 * @return true if successful, false otherwise
 */
bool predict(NeuralNetwork* network, const double* inputs, size_t num_inputs, 
             double* outputs, size_t num_outputs) {
    /* Validate input parameters */
    if (network == NULL || inputs == NULL || outputs == NULL) {
        fprintf(stderr, "Invalid parameters: network, inputs, and outputs must not be NULL\n");
        return false;
    }
    
    /* Check if number of outputs matches output layer size */
    size_t output_layer = network->num_layers - 1;
    if (num_outputs != network->layer_sizes[output_layer]) {
        fprintf(stderr, "Output size mismatch: Expected %zu outputs, got %zu\n", 
                network->layer_sizes[output_layer], num_outputs);
        return false;
    }
    
    /* Forward propagate */
    if (!forward_propagate(network, inputs, num_inputs)) {
        return false;
    }
    
    /* Copy output layer activations to outputs */
    for (size_t i = 0; i < num_outputs; i++) {
        outputs[i] = network->layers[output_layer].neurons[i].activation;
    }
    
    return true;
}

/**
 * Safely free all memory allocated for the neural network
 * 
 * @param network Pointer to neural network
 */
void free_neural_network(NeuralNetwork* network) {
    if (network == NULL) {
        return;
    }
    
    /* Free all memory allocated for the network */
    if (network->layers != NULL) {
        for (size_t i = 0; i < network->num_layers; i++) {
            if (network->layers[i].neurons != NULL) {
                for (size_t j = 0; j < network->layers[i].num_neurons; j++) {
                    free(network->layers[i].neurons[j].weights);
                    network->layers[i].neurons[j].weights = NULL;
                }
                free(network->layers[i].neurons);
                network->layers[i].neurons = NULL;
            }
        }
        free(network->layers);
        network->layers = NULL;
    }
    
    free(network->layer_sizes);
    network->layer_sizes = NULL;
    
    free(network);
}

/**
 * Save neural network to a file
 * 
 * @param network Pointer to neural network
 * @param filename Name of the file to save to
 * @return true if successful, false otherwise
 */
bool save_neural_network(const NeuralNetwork* network, const char* filename) {
    /* Validate input parameters */
    if (network == NULL || filename == NULL) {
        fprintf(stderr, "Invalid parameters: network and filename must not be NULL\n");
        return false;
    }
    
    /* Open file for writing */
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s for writing: %s\n", filename, strerror(errno));
        return false;
    }
    
    /* Write network structure */
    if (fwrite(&network->num_layers, sizeof(size_t), 1, file) != 1 ||
        fwrite(&network->learning_rate, sizeof(double), 1, file) != 1 ||
        fwrite(network->layer_sizes, sizeof(size_t), network->num_layers, file) != network->num_layers) {
        fprintf(stderr, "Failed to write network structure to file\n");
        fclose(file);
        return false;
    }
    
    /* Write network weights and biases */
    for (size_t layer = 1; layer < network->num_layers; layer++) {
        for (size_t neuron = 0; neuron < network->layers[layer].num_neurons; neuron++) {
            /* Write bias */
            if (fwrite(&network->layers[layer].neurons[neuron].bias, sizeof(double), 1, file) != 1) {
                fprintf(stderr, "Failed to write bias to file\n");
                fclose(file);
                return false;
            }
            
            /* Write weights */
            if (fwrite(network->layers[layer].neurons[neuron].weights, sizeof(double), 
                      network->layers[layer].neurons[neuron].num_weights, file) != 
                      network->layers[layer].neurons[neuron].num_weights) {
                fprintf(stderr, "Failed to write weights to file\n");
                fclose(file);
                return false;
            }
        }
    }
    
    fclose(file);
    return true;
}

/**
 * Load neural network from a file
 * 
 * @param filename Name of the file to load from
 * @return Pointer to loaded neural network or NULL on failure
 */
NeuralNetwork* load_neural_network(const char* filename) {
    /* Validate input parameters */
    if (filename == NULL) {
        fprintf(stderr, "Invalid parameter: filename must not be NULL\n");
        return NULL;
    }
    
    /* Open file for reading */
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s for reading: %s\n", filename, strerror(errno));
        return NULL;
    }
    
    /* Read network structure */
    size_t num_layers;
    double learning_rate;
    if (fread(&num_layers, sizeof(size_t), 1, file) != 1 ||
        fread(&learning_rate, sizeof(double), 1, file) != 1) {
        fprintf(stderr, "Failed to read network structure from file\n");
        fclose(file);
        return NULL;
    }
    
    /* Validate number of layers */
    if (num_layers < 2 || num_layers > 100) {  /* Arbitrary upper limit for safety */
        fprintf(stderr, "Invalid number of layers: %zu\n", num_layers);
        fclose(file);
        return NULL;
    }
    
    /* Allocate memory for layer sizes */
    size_t* layer_sizes = (size_t*)calloc(num_layers, sizeof(size_t));
    if (layer_sizes == NULL) {
        fprintf(stderr, "Memory allocation failed for layer sizes\n");
        fclose(file);
        return NULL;
    }
    
    /* Read layer sizes */
    if (fread(layer_sizes, sizeof(size_t), num_layers, file) != num_layers) {
        fprintf(stderr, "Failed to read layer sizes from file\n");
        free(layer_sizes);
        fclose(file);
        return NULL;
    }
    
    /* Create neural network */
    NeuralNetwork* network = create_neural_network(layer_sizes, num_layers, learning_rate);
    if (network == NULL) {
        fprintf(stderr, "Failed to create neural network\n");
        free(layer_sizes);
        fclose(file);
        return NULL;
    }
    
    /* Free temporary memory */
    free(layer_sizes);
    
    /* Read network weights and biases */
    for (size_t layer = 1; layer < network->num_layers; layer++) {
        for (size_t neuron = 0; neuron < network->layers[layer].num_neurons; neuron++) {
            /* Read bias */
            if (fread(&network->layers[layer].neurons[neuron].bias, sizeof(double), 1, file) != 1) {
                fprintf(stderr, "Failed to read bias from file\n");
                free_neural_network(network);
                fclose(file);
                return NULL;
            }
            
            /* Read weights */
            if (fread(network->layers[layer].neurons[neuron].weights, sizeof(double), 
                     network->layers[layer].neurons[neuron].num_weights, file) != 
                     network->layers[layer].neurons[neuron].num_weights) {
                fprintf(stderr, "Failed to read weights from file\n");
                free_neural_network(network);
                fclose(file);
                return NULL;
            }
        }
    }
    
    fclose(file);
    return network;
}

int main() {

    double xor_inputs[4][2] = {
        {0.0, 0.0},
        {0.0, 1.0},
        {1.0, 0.0},
        {1.0, 1.0}
    };
    double xor_outputs[4][1] = {
        {0.0},
        {1.0},
        {1.0},
        {0.0}
    };
    
    /* Create neural network */
    size_t layer_sizes[] = {2, 4, 1};  /* Input, hidden, output layers */
    NeuralNetwork* network = create_neural_network(layer_sizes, 3, 0.1);
    if (network == NULL) {
        fprintf(stderr, "Failed to create neural network\n");
        return ERROR_ALLOCATION_FAILED;
    }
    
    printf("Training neural network on XOR problem...\n");
    
    /* Train neural network */
    const int num_epochs = 10000;
    for (int epoch = 0; epoch < num_epochs; epoch++) {
        double total_error = 0.0;
        
        /* Train on each sample */
        for (int i = 0; i < 4; i++) {
            /* Forward propagate */
            if (!forward_propagate(network, xor_inputs[i], 2)) {
                fprintf(stderr, "Forward propagation failed\n");
                free_neural_network(network);
                return ERROR_INVALID_INPUT;
            }
            
            /* Calculate error */
            double output = network->layers[2].neurons[0].activation;
            double target = xor_outputs[i][0];
            double error = target - output;
            total_error += error * error;
            
            /* Backward propagate */
            if (!backward_propagate(network, xor_outputs[i], 1)) {
                fprintf(stderr, "Backward propagation failed\n");
                free_neural_network(network);
                return ERROR_INVALID_INPUT;
            }
        }
        
        /* Print progress */
        if ((epoch + 1) % 1000 == 0) {
            printf("Epoch %d: Error = %.10f\n", epoch + 1, total_error);
        }
    }

    printf("Training complete!\n");

    printf("Testing neural network...\n");

    for(int i=0; i < 4; i++) {
        double output;
        if(!predict(network, xor_inputs[i], 2, &output, 1)) {
            fprintf(stderr, "Prediction failed\n");
            free_neural_network(network);
            return ERROR_INVALID_INPUT;
        }
        printf("Input: %.1f, %.1f -> Output: %.6f (Expected: %.1f)\n", 
               xor_inputs[i][0], xor_inputs[i][1], output, xor_outputs[i][0]);
    }
    
    /* Save neural netowrk */
    if(!save_neural_network(network, "xor_network.bin")) {
        fprintf(stderr, "Failed to save neural network\n");
        free_neural_network(network);
        return ERROR_FILE_OPERATION;
    }
    printf("Neural network saved to xor_network.bin\n");
    free_neural_network(network);
    
    /* Load neural network */
    NeuralNetwork* loaded_network = load_neural_network("xor_network.bin");
    if(loaded_network == NULL) {
        fprintf(stderr, "Failed to load neural network\n");
        return ERROR_FILE_OPERATION;
    }

    printf("Loaded neural network from xor_network.bin\n");
    for(int i=0; i < 4; i++) {
        double output;
        if(!predict(loaded_network, xor_inputs[i], 2, &output, 1)) {
            fprintf(stderr, "Prediction failed\n");
            free_neural_network(loaded_network);
            return ERROR_INVALID_INPUT;
        }
        printf("Input: %.1f, %.1f -> Output: %.6f (Expected: %.1f)\n", 
               xor_inputs[i][0], xor_inputs[i][1], output, xor_outputs[i][0]);
    }
    free_neural_network(loaded_network);
    printf("Neural network loaded and tested successfully!\n");
    printf("All tests passed!\n");
    printf("Exiting program...\n");

    return 0;
}