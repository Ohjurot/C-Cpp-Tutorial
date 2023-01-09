#include "Pet.hpp"

#include <sstream>

PetManager::Pet::Pet(const std::string_view& name) :
    m_name(name)
{
}

void PetManager::Pet::Lived()
{
    if (!m_living)
    {
        throw std::logic_error("A pet that already died can't live again!");
    }

    m_ageInDays++;
}

void PetManager::Pet::Died()
{
    m_living = false;
}

std::ostream& operator<<(std::ostream& os, const PetManager::Pet& pet)
{
    os << pet.GetKind() << " \"" << pet.GetName() << "\" (Age: " << pet.GetAge() << " " << (pet.IsLiving() ? "Living" : "Dead") << ")";
    return os;
}
