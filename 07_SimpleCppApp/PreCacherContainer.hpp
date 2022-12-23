#pragma once

#include "FunctionPreCacher.hpp"

#include <iostream>
#include <stdexcept>

namespace SimpleApp
{
    template<typename T, typename Pc = FunctionPreCacher<T>>
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
            void Append(const Pc& pc)
            {
                if (m_usage >= 8)
                    throw std::overflow_error("PreCacherContainer Container overflown");
                m_preCachers[m_usage++] = pc;
            }
            void Append(Pc&& pc)
            {
                if (m_usage >= 8)
                    throw std::overflow_error("PreCacherContainer Container overflown");
                m_preCachers[m_usage++] = std::move(pc);
            }
            const Pc& At(int index) const
            {
                if (index >= 8 || index < 0) 
                    throw std::range_error("PreCacherContainer index out of range");
                return m_preCachers[index];
            }
            Pc& At(int index)
            {
                if (index >= 8 || index < 0)
                    throw std::range_error("PreCacherContainer index out of range");
                return m_preCachers[index];
            }
            int Size() const noexcept
            {
                return m_usage;
            }

            PreCacherContainer& operator<<(const Pc& pc)
            {
                Append(pc);
                return *this;
            }
            PreCacherContainer& operator<<(Pc&& pc)
            {
                Append(std::move(pc));
                return *this;
            }
            const Pc& operator[](int index) const
            {
                return At(index);
            }
            Pc& operator[](int index)
            {
                return At(index);
            }

        private:
            Pc m_preCachers[8];
            int m_usage = 0;
    };
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const SimpleApp::PreCacherContainer<T>& pc)
{
    pc.Print(os);
    return os;
}
