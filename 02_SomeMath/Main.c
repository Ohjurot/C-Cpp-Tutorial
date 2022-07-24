#include <stdio.h>

int main()
{
    // -10
    int x = -10;
    int y = x * x + 2 * x + 5;
    printf("f(%i) = %i\n", x, y); 
    // 0
    x = 0;
    y = x * x + 2 * x + 5;
    printf("f(%i) = %i\n", x, y);
    // 10
    x = 10;
    y = x * x + 2 * x + 5;
    printf("f(%i) = %i\n", x, y);
}
