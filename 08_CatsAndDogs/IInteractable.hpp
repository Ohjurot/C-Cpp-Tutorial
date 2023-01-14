#pragma once

#include <string>

namespace PetManager
{
    template<typename Return, typename... Args>
    class IInteractable
    {
        public:
            virtual ~IInteractable() = default;

            virtual Return Interact(Args... args) = 0;
    };
}
