#pragma once

#include <string>
#include <ostream>
#include <string_view>
#include <stdexcept>

#include <iostream>

namespace PetManager
{
    class Pet
    {
        public:
            Pet(const std::string_view& name);
            virtual ~Pet() = default;

            void Lived();
            void Died();

            virtual std::string_view GetKind() const noexcept
            {
                return "Pet";
            }

            inline const std::string& GetName() const noexcept
            {
                return m_name;
            }
            inline bool IsLiving() const noexcept
            {
                return m_living;
            }
            inline size_t GetAge() const noexcept
            {
                return m_ageInDays;
            }

        private:
            std::string m_name;
            bool m_living = true;
            size_t m_ageInDays = 0;
    };
}

std::ostream& operator<<(std::ostream& os, const PetManager::Pet& pet);
