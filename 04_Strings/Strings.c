#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    const char* string = "Hello World!";

    char edit[256];
    edit[0] = 'L';
    edit[1] = 'O';
    edit[2] = 'L';
    edit[3] = '\0';

    printf(string);
}
