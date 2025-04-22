#include <stdio.h>
#include <immintrin.h>
#include <stdint.h>

// Function to check AVX2 support using CPUID
int is_avx2_supported() {
    uint32_t eax, ebx, ecx, edx;
    eax = 7;  // Extended features query
    ecx = 0;

    // Execute CPUID
    asm volatile ("cpuid"
                  : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                  : "a"(eax), "c"(ecx));

    // Check AVX2 support (Bit 5 in EBX)
    return (ebx & (1 << 5)) != 0;
}

int main() {
    int dataA[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int dataB[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    int result[8];

    if (is_avx2_supported()) {
        printf("AVX2 Supported: Using vectorized operations.\n");

        // Perform AVX2 vectorized addition
        __m256i a = _mm256_loadu_si256((__m256i*)dataA);
        __m256i b = _mm256_loadu_si256((__m256i*)dataB);
        __m256i res = _mm256_add_epi32(a, b);
        _mm256_storeu_si256((__m256i*)result, res);
    } else {
        printf("AVX2 Not Supported: Using fallback loop.\n");

        // Fallback to scalar addition
        for (int i = 0; i < 8; i++) {
            result[i] = dataA[i] + dataB[i];
        }
    }

    // Print results
    printf("Result: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
