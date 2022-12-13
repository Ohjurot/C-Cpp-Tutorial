#pragma once

#include "FunctionPreCacher.hpp"

#include <iostream>
#include <stdexcept>

namespace SimpleApp
{
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
                    os << m_preCachers[i];
                }
            }
            void Append(const FunctionPreCacher& pc)
            {
                if (m_usage >= 8)
                    throw std::overflow_error("PreCacherContainer Container overflown");
                m_preCachers[m_usage++] = pc;
            }
            void Append(FunctionPreCacher&& pc)
            {
                if (m_usage >= 8)
                    throw std::overflow_error("PreCacherContainer Container overflown");
                m_preCachers[m_usage++] = std::move(pc);
            }
            const FunctionPreCacher& At(int index) const
            {
                if (index >= 8 || index < 0) 
                    throw std::range_error("PreCacherContainer index out of range");
                return m_preCachers[index];
            }
            FunctionPreCacher& At(int index)
            {
                if (index >= 8 || index < 0)
                    throw std::range_error("PreCacherContainer index out of range");
                return m_preCachers[index];
            }
            int Size() const noexcept
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
}

inline std::ostream& operator<<(std::ostream& os, const SimpleApp::PreCacherContainer& pc)
{
    pc.Print(os);
    return os;
}
