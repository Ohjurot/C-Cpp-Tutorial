#pragma once

#include "Pet.hpp"

namespace PetManager
{
    class Dog : 
        public Pet, 
        public Pet::ToyInteractable
    {
        public:
            using Pet::Pet;

            std::string_view GetKind() const noexcept override
            {
                return "Dog";
            }

            std::string Interact(Toy& toy) override
            {
                if (dynamic_cast<ToyMouse*>(&toy))
                {
                    return "Barks!";
                }
                else if (dynamic_cast<ToyBone*>(&toy))
                {
                    return "Chewing...";
                }
                
                return "Looks confused...";
            }
    };
}
