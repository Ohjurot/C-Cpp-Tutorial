#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef size_t accumulateInt;
typedef struct // 16 Bytes big
{
    accumulateInt sum;
    accumulateInt num;
} accumulateData;

void newAccumulateData(accumulateData* data)
{
    data->sum = 0;
    data->num = 0;
}
void accumulate(accumulateData* data, accumulateInt value)
{
    data->sum += value;
    data->num++;
}
accumulateInt accumulateResult(accumulateData* data)
{
    return data->sum / data->num;
}

int main()
{
    accumulateData data;
    newAccumulateData(&data);

    accumulate(&data, 10);
    accumulate(&data, 20);
    accumulate(&data, 50);

    accumulateInt avg = accumulateResult(&data);
    printf("The average is: %lli", avg);
}
