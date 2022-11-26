#include <iostream>
#include <cstdint>

int32_t f(int32_t x)
{
    return x * x + 5 * x + 5;
}

int main()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    std::cout << "Starting at: " << x << " Number of itterations: " << count << std::endl;
    for (uint32_t i = 1; i <= count; i++)
        std::cout << "f(" << i * x << ") = " << f(i * x) << std::endl;
}
