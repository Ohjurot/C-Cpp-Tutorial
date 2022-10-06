#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint64_t GetUIDa()
{
    static uint64_t id = 0;
    return id++;
}

uint64_t GetUIDb()
{
    static uint64_t id = 0;
    return id++;
}

int main()
{
    for (uint64_t i = 0; i < 64; i++)
    {
        uint64_t uida = GetUIDa();
        uint64_t uidb = GetUIDb();
        printf("UIDa: %"PRIu64" & UIDb: %"PRIu64"\n", uida, uidb);
    }

    const int32_t count = 32;
    const int32_t size = count * sizeof(int32_t);

    int32_t* const arrayA = malloc(size);
    int32_t* const arrayB = malloc(size);

    if (arrayA && arrayB)
    {
        // Init arrays
        for (int32_t i = 0; i < count; i++)
        {
            arrayA[i] = i * 11;
        }
        memset(arrayB, 0xFF, size);

        // Compared arrays
        int32_t abEqual = memcmp(arrayA, arrayB, size) == 0;
        printf("Arrays equal bevore copy: %i; ", abEqual);

        // Copy arrays
        memcpy(arrayB, arrayA, size);

        // Compared arrays
        abEqual = memcmp(arrayA, arrayB, size) == 0;
        printf("Arrays equal after copy: %i", abEqual);
    }

    // Free memory
    if (arrayA) free(arrayA);
    if (arrayB) free(arrayB);
}
