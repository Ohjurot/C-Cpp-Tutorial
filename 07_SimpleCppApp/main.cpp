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
        void Print(std::ostream& os = std::cout) const
        {
            if (values)
            {
                for (uint32_t i = 1; i <= count; i++)
                    os << "f(" << i * x << ") = " << values[i - 1] << std::endl;
            }
        }   
        int32_t At(uint32_t index) const
        {
            // TODO: Check range
            return values[index];
        }
        uint32_t Size() const
        {
            return count;
        }

        FunctionPreCacher& operator()()
        {
            return Compute();
        }
        FunctionPreCacher& operator()(int32_t x, uint32_t count, int32_t(*function)(int32_t))
        {
            Setup(x, count, function);
            return Compute();
        }
        int32_t operator[](uint32_t index) const
        {
            return At(index);
        }
        operator bool()
        {
            return values != nullptr;
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

        void Print(std::ostream& os = std::cout) const
        {
            os << "Container at " << this << std::endl;
            for (int i = 0; i < m_usage; i++)
            {
                os << "FunctionPreCacher #" << (i + 1) << std::endl;
                m_preCachers[i].Print(os);
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
        const FunctionPreCacher& At(int index) const
        {
            return m_preCachers[index];
        }
        FunctionPreCacher& At(int index)
        {
            return m_preCachers[index];
        }
        int Size() const
        {
            return m_usage;
        }

        PreCacherContainer& operator<<(const FunctionPreCacher& pc)
        {
            Append(pc);
            return *this;
        }
        PreCacherContainer& operator<<(FunctionPreCacher&& pc)
        {
            Append(std::move(pc));
            return *this;
        }
        const FunctionPreCacher& operator[](int index) const
        {
            return At(index);
        }
        FunctionPreCacher& operator[](int index)
        {
            return At(index);
        }

    private:
        FunctionPreCacher m_preCachers[8];
        int m_usage = 0;
};

std::ostream& operator<<(std::ostream& os, const PreCacherContainer& pc)
{
    pc.Print(os);
    return os;
}

int main()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    PreCacherContainer cnt;
    cnt << std::move(FunctionPreCacher(x, count, &f)())
        << std::move(FunctionPreCacher(x * 2, count, &f)())
        << std::move(FunctionPreCacher(x, count * 2, &f)())
        << std::move(FunctionPreCacher(x * 2, count * 2, &f)());

    std::cout << cnt;
}
