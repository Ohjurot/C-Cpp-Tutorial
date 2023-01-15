#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"
#include "LinkedList.hpp"

int main()
{
    using namespace PetManager;
    using namespace FuselUtil;

    Cat tabby("Tabby");
    Dog oscar("Oscar");

    LinkedList<Pet*> pets;
    pets.Append(&tabby); 
    pets.Append(&oscar);

    for (const Pet* pet : pets)
    {
        std::cout << *pet << std::endl;
    }

    pets.Erase(pets.Count() - 1);

    for (const Pet* pet : pets)
    {
        std::cout << *pet << std::endl;
    }

    ToyBone bone;
    ToyMouse mouse;

    std::cout << "Playing with our pets: " << std::endl;
    std::cout << oscar.GetName() << " gets the bone: " << oscar.Interact(bone) << std::endl;
    std::cout << oscar.GetName() << " gets the mouse: " << oscar.Interact(mouse) << std::endl;
    std::cout << tabby.GetName() << " gets the bone: " << tabby.Interact(bone) << std::endl;
    std::cout << tabby.GetName() << " gets the mouse: " << tabby.Interact(mouse) << std::endl;
    std::cout << std::endl;

    tabby.Lived(); oscar.Lived();
    tabby.Lived(); oscar.Lived();
    tabby.Lived(); oscar.Lived();
    tabby.Lived(); oscar.Died();
    tabby.Lived();

    std::cout << "Sad story about " << oscar.GetName() << std::endl;
    std::cout << tabby << std::endl;
    std::cout << oscar << std::endl;
    std::cout << "RIP " << oscar.GetName() << "!" << std::endl;
}
