#include <stdio.h>
#include <stdint.h>

void accumulate(int64_t* sum, int64_t* num, int64_t value)
{
    *sum += value;
    (*num)++;
}

int main()
{
    int64_t sum = 0; // Sum of all values
    int64_t num = 0; // Numer of sums

    accumulate(&sum, &num, 10);
    accumulate(&sum, &num, 20);

    int64_t avg = sum / num;
    printf("The average is: %lli", avg);
}
