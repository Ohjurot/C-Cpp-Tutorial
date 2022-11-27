#include <iostream>
#include <cstdint>

int32_t f(int32_t x)
{
    return x * x + 5 * x + 5;
}

class FunctionPreCacher
{
    public:
        void Setup(int32_t x, uint32_t count, int32_t(*function)(int32_t))
        {
            if (!values)
            {
                this->x = x;
                this->count = count;
                this->function = function;
            }
        }

        void Compute()
        {
            if (function && count > 0)
            {
                Release();
                values = new int32_t[count];
                if (values)
                {
                    for (uint32_t i = 1; i <= count; i++)
                    {
                        values[i - 1] = function(i * x);
                    }
                }
            }
        }

        void Release()
        {
            if (values)
            {
                delete[] values;
                values = nullptr;
            }
        }

        void Print()
        {
            if (values)
            {
                for (uint32_t i = 1; i <= count; i++)
                    std::cout << "f(" << i * x << ") = " << values[i - 1] << std::endl;
            }
        }   

    private:
        int32_t* values = nullptr;
        int32_t x = 0;
        uint32_t count = 0;
        int32_t(*function)(int32_t x) = nullptr;
};

int main()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    FunctionPreCacher pc;
    pc.Setup(x, count, &f);
    pc.Compute();
    pc.Print();
    pc.Release();
}
