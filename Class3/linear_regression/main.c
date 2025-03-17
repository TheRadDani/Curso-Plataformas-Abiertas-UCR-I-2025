#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define LEARNING_RATE 0.0001
#define ITERATIONS 10000
#define DATASET_SIZE 100

// Structure to hold data
typedef struct {
    double x;
    double y;
} DataPoint;

// Box-Muller transform to generate Gaussian samples
double random_normal(double mean, double stddev) {
    double u1 = (rand() + 1.0) / (RAND_MAX + 1.0);
    double u2 = (rand() + 1.0) / (RAND_MAX + 1.0);
    return mean + stddev * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

// Function to read dataset
int read_data(DataPoint data[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return -1;
    }
    
    char header[100];  // Skip header
    fgets(header, 100, file);
    
    int count = 0;
    while (fscanf(file, "%lf\t%lf", &data[count].x, &data[count].y) == 2) {
        count++;
    }
    
    fclose(file);
    return count;
}

// Function to compute cost
double compute_cost(DataPoint data[], int size, double w, double b) {
    double total_error = 0;
    for (int i = 0; i < size; i++) {
        double prediction = w * data[i].x + b;
        double error = data[i].y - prediction;
        total_error += error * error;
    }
    return total_error / size;
}

// Function to perform gradient descent
void gradient_descent(DataPoint data[], int size, double *w, double *b) {
    double dw, db;
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        dw = 0;
        db = 0;
        
        for (int i = 0; i < size; i++) {
            double prediction = (*w) * data[i].x + (*b);
            double error = data[i].y - prediction;
            dw += -2 * data[i].x * error;
            db += -2 * error;
        }
        
        dw /= size;
        db /= size;

        *w -= LEARNING_RATE * dw;
        *b -= LEARNING_RATE * db;
        
        if (iter % 1000 == 0) {
            printf("Iteration %d: Cost = %lf\n", iter, compute_cost(data, size, *w, *b));
        }
    }
}

int main() {
    DataPoint data[DATASET_SIZE];
    
    int size = read_data(data, "data.tsv");
    if (size <= 0) return 1;
    // 0 initialization
    //double w = 0, b = 0;
    srand(time(NULL));
    double w = random_normal(0, 0.1);
    double b = random_normal(0, 0.1);
    printf("Initial w: %lf, Initial b: %lf\n", w, b);
    printf("Starting training...\n");
    gradient_descent(data, size, &w, &b);
    
    printf("Final model: y = %.4lf * x + %.4lf\n", w, b);
    
    return 0;
}
