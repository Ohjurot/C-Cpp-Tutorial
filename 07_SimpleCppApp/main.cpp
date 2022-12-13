#include "SimpleApp.hpp"

#include <iostream>
#include <exception>

int main() noexcept
{
    try 
    {
        return SimpleApp::SaveMain();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception occured: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception occured!" << std::endl;
    }
    return -1;
}
