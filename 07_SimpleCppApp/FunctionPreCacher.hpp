#pragma once

#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <cstring>

namespace SimpleApp
{
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
                    else
                    {
                        throw std::runtime_error("FunctionPreCacher new failed!");
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
                    else
                    {
                        throw std::runtime_error("FunctionPreCacher new failed!");
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
                if (index >= count)
                    throw std::range_error("FunctionPreCacher index out of range!");
                return values[index];
            }
            uint32_t Size() const noexcept
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
}

inline std::ostream& operator<<(std::ostream& os, const SimpleApp::FunctionPreCacher& pc)
{
    pc.Print(os);
    return os;
}
