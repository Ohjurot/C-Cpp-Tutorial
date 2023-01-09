#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
    using namespace PetManager;

    Cat tabby("Tabby");
    Dog oscar("Oscar");
    
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
