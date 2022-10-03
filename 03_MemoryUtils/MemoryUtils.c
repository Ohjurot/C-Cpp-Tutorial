#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <string.h>

int main()
{
    int32_t arrayA[32];
    int32_t arrayB[32];

    // Init arrays
    for (int32_t i = 0; i < 32; i++)
    {
        arrayA[i] = i * 11;
    }
    memset(arrayB, 0xFF, 32 * sizeof(int32_t));

    // Compared arrays
    int32_t abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
    printf("Arrays equal bevore copy: %i; ", abEqual);

    // Copy arrays
    memcpy(arrayB, arrayA, 32 * sizeof(int32_t));

    // Compared arrays
    abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
    printf("Arrays equal after copy: %i", abEqual);
}
