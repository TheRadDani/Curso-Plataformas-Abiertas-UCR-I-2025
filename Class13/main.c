#include <stdio.h>

int main() {
    int x;
    x = 10;
    int y = 7;
    int* p = &x;
    int q = 0;

    int arr[3] = {1, 2, 3};

    int* ptr = arr; //Pointer to the first element of arr

    printf("Element of arr: %d\n", *ptr);

    ptr++;

    printf("Element of arr: %d\n", *ptr);

    size_t size = sizeof(arr) / sizeof(int);

    ptr--;

    for(size_t i = 0; i < size; i++) {
        printf("Element of arr->: %d\n", *(ptr + i));
    }


    printf("address of x: %p\n", (p+1));
    printf("address of x: %p\n", (int*)&x);
    printf("%d\n", *(p + 2));
    return 0;
}