#include <stdlib.h>

int compare(const void* a, const void* b) {
    
}

int main() {
    int arr = {5, 2, 8, 1, 4};
    qsort(arr, 5, sizeof(int), compare);
    // arr {1, 2, 4, 5, 8}
    return 0;
}