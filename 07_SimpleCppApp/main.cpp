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
        FunctionPreCacher(FunctionPreCacher&& other) noexcept
        {
            x = other.x;
            count = other.count;
            function = other.function;
            values = other.values;

            other.values = nullptr;
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

        FunctionPreCacher& operator=(FunctionPreCacher&& other) noexcept
        {
            if (this != &other)
            {
                this->~FunctionPreCacher();
                this->FunctionPreCacher::FunctionPreCacher(std::move(other));
            }

            return *this;
        }

        void Setup(int32_t x, uint32_t count, int32_t(*function)(int32_t))
        {
            Release();
            this->x = x;
            this->count = count;
            this->function = function;
        }

        FunctionPreCacher& Compute()
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

            return *this;
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

class PreCacherContainer
{
    public:
        PreCacherContainer() = default;
        PreCacherContainer(const PreCacherContainer&) = default;
        PreCacherContainer(PreCacherContainer&&) noexcept = default;
        ~PreCacherContainer() = default;

        PreCacherContainer& operator=(const PreCacherContainer&) = default;
        PreCacherContainer& operator=(PreCacherContainer&&) noexcept = default;

        void Print() const
        {
            std::cout << "Container at " << this << std::endl;
            for (int i = 0; i < m_usage; i++)
            {
                std::cout << "FunctionPreCacher #" << (i + 1) << std::endl;
                m_preCachers[i].Print();
            }
        }

        void Append(const FunctionPreCacher& pc)
        {
            if (m_usage < 8)
            {
                m_preCachers[m_usage++] = pc;
            }
        }

        void Append(FunctionPreCacher&& pc)
        {
            if (m_usage < 8)
            {
                m_preCachers[m_usage++] = std::move(pc);
            }
        }

    private:
        FunctionPreCacher m_preCachers[8];
        int m_usage = 0;
};

int main()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    PreCacherContainer cnt;
    cnt.Append(std::move(FunctionPreCacher(x, count, &f).Compute()));
    cnt.Append(std::move(FunctionPreCacher(x * 2, count, &f).Compute()));
    cnt.Append(std::move(FunctionPreCacher(x, count * 2, &f).Compute()));
    cnt.Append(std::move(FunctionPreCacher(x * 2, count * 2, &f).Compute()));
    cnt.Print();
}
