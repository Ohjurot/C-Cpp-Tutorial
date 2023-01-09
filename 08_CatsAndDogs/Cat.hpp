#pragma once

#include "Pet.hpp"

namespace PetManager
{
    class Cat : public Pet
    {
        public:
            using Pet::Pet;

            std::string_view GetKind() const noexcept override
            {
                return "Cat";
            }
    };
}
