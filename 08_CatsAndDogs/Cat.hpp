#pragma once

#include "Pet.hpp"

namespace PetManager
{
    class Cat : 
        public Pet, 
        public Pet::ToyInteractable
    {
        public:
            using Pet::Pet;

            std::string_view GetKind() const noexcept override
            {
                return "Cat";
            }

            std::string Interact(Toy& toy) override
            {
                if (dynamic_cast<ToyMouse*>(&toy))
                {
                    return "Jump!";
                }
                else
                {
                    return "Looks confused...";
                }
            }
    };
}
