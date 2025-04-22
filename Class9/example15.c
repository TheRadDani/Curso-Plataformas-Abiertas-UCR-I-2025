/*
* Intrinsics allow direct access to AVX instructions without writing assembly.
* Example: Vectorized addition using AVX2 intrinsics.
*/

#include <immintrin.h>
#include <stdio.h>

int main() {
    __m256i a = _mm256_set1_epi32(5);  // Set all elements to 5
    __m256i b = _mm256_set1_epi32(3);  // Set all elements to 3
    __m256i result = _mm256_add_epi32(a, b);  // Vectorized addition

    int output[8];
    _mm256_storeu_si256((__m256i*)output, result); // Stores results back to memory.

    printf("Result: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
