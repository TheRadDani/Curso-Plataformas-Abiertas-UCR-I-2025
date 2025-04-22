#include <stdio.h>
#include <immintrin.h>

#define USE_AVX2  // Enable AVX2 optimization

int main() {
    int dataA[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int dataB[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    int result[8];

#ifdef USE_AVX2
    __m256i a = _mm256_loadu_si256((__m256i*)dataA);
    __m256i b = _mm256_loadu_si256((__m256i*)dataB);
    __m256i res = _mm256_add_epi32(a, b);
    _mm256_storeu_si256((__m256i*)result, res);
#else
    for (int i = 0; i < 8; i++) {
        result[i] = dataA[i] + dataB[i];  // Fallback non-vectorized loop
    }
#endif

    printf("Result: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
