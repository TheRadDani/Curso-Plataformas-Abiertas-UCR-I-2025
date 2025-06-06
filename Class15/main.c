#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4

typedef struct {
    int *array;
    int start_index;
    int end_index;
    long partial_sum;
} ThreadData;

void* compute_partial_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0;

    for(int i = data->start_index; i < data->end_index; i++) {
        data->partial_sum += data->array[i];
    }

    return NULL;
}

int main() {
    int array[ARRAY_SIZE];
    long total_sum = 0;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // n(n+1) / 2
    for(int i=0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    // Calculate the size of each segment for each thread
    int chuck_size = ARRAY_SIZE / NUM_THREADS;

    // Create threads to compute partial sums and assign work
    for(int i = 0; i <  NUM_THREADS; i++) {
        thread_data[i].array = array;
        thread_data[i].start_index = i * chuck_size;
        thread_data[i].end_index = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chuck_size;
        
        pthread_create(&threads[i], NULL, compute_partial_sum, &thread_data[i]);
    }

    // Wait for all threads to finish and collect results
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    // Verify result sum of first n integers: // n(n+1) / 2
    long expected_sum = (long)ARRAY_SIZE * (ARRAY_SIZE + 1) / 2;
    printf("Total sum: %ld\n", total_sum);
    printf("Expected sum: %ld\n", expected_sum);
    if (total_sum == expected_sum) {
        printf("Sum is correct!\n");
    } else {
        printf("Sum is incorrect!\n");
    }
    return 0;
}


