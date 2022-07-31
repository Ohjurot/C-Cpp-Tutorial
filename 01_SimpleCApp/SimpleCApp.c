#include <stdio.h>
#include <stdint.h>

int main()
{
	// (I) Simulate input (TODO: Replace with proper input)
	int32_t x = 5;

	// (P)
	int32_t y = x * x + 5 * x + 5;

	// (O)
	printf("f(%i) = %i", x, y);
}
