#pragma once

#include "Pet.hpp"

namespace PetManager
{
    class Dog : public Pet
    {
        public:
            using Pet::Pet;

            std::string_view GetKind() const noexcept override
            {
                return "Dog";
            }
    };
}
