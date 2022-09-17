#include <stdio.h>
#include <stdint.h>

int32_t f(int32_t x);
int scan_x(int32_t* x);
void print_fx(int32_t x, int32_t y);

int main()
{
	// (I) 
	int32_t x = 0;
	int result = scan_x(&x);
	printf("Read %i parameters from user input. ", result);

	// (P) 
	int32_t y1 = f(1 * x);
	int32_t y2 = f(2 * x);
	int32_t y3 = f(3 * x);
	int32_t y4 = f(4 * x);

	// (O)
	print_fx(1 * x, y1);
	print_fx(2 * x, y2);
	print_fx(3 * x, y3);
	print_fx(4 * x, y4);
}

int32_t f(int32_t x)
{
	return x * x + 5 * x + 5;
}

int scan_x(int32_t* x)
{
	printf("Enter the value x: ");
	return scanf_s("%i", x);
}

void print_fx(int32_t x, int32_t y)
{
	printf("f(%i) = %i, ", x, y);
}
