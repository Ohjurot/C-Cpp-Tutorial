#include <stdio.h>
#include <stdint.h>

struct accumulateData // 16 Bytes big
{
    int64_t sum;
    int64_t num;
};
void newAccumulateData(struct accumulateData* data)
{
    data->sum = 0;
    data->num = 0;
}
void accumulate(struct accumulateData* data, int64_t value)
{
    data->sum += value;
    data->num++;
}
int64_t accumulateResult(struct accumulateData* data)
{
    return data->sum / data->num;
}

int main()
{
    struct accumulateData data;
    newAccumulateData(&data);

    accumulate(&data, 10);
    accumulate(&data, 20);
    accumulate(&data, 30);

    int64_t avg = accumulateResult(&data);
    printf("The average is: %lli", avg);
}
