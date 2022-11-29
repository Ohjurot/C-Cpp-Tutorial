#include <iostream>
#include <cstdlib>
#include <cstdint>

int32_t f(int32_t x)
{
    return x * x + 5 * x + 5;
}

class FunctionPreCacher
{
    public:
        FunctionPreCacher() = default;
        FunctionPreCacher(const FunctionPreCacher& other)
        {
            x = other.x;
            count = other.count;
            function = other.function;
            
            if (other.values)
            {
                values = new int32_t[other.count];
                if (values)
                {
                    std::memcpy(values, other.values, sizeof(int32_t) * other.count);
                }
            }
        }
        FunctionPreCacher(int32_t x, uint32_t count, int32_t(*function)(int32_t))
        {
            Setup(x, count, function);
        }
        ~FunctionPreCacher()
        {
            Release();
        }

        FunctionPreCacher& operator=(const FunctionPreCacher& other)
        {
            if (this != &other)
            {
                this->~FunctionPreCacher();
                this->FunctionPreCacher::FunctionPreCacher(other);
            }

            return *this;
        }

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

        void Print() const
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

void PrintPc(const FunctionPreCacher& pc)
{
    pc.Print();
}

int main()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    FunctionPreCacher pc(x, count, &f);
    pc.Compute();
    PrintPc(pc);
}
