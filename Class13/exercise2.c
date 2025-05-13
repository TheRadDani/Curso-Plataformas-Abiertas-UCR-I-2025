#include <stdlib.h>
#include <stdio.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[5] = {5, 2, 8, 1, 4};
    qsort(arr, 5, sizeof(int), compare);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // arr {1, 2, 4, 5, 8}
    return 0;
}