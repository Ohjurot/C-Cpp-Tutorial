#include "SimpleApp.hpp"

int SimpleApp::SaveMain()
{
    int32_t x;
    uint32_t count;
    std::cout << "Enter the starting value: ";
    std::cin >> x;
    std::cout << "Enter the itterations: ";
    std::cin >> count;

    PreCacherContainer cnt;
    cnt << std::move(FunctionPreCacher(x, count, &f)())
        << std::move(FunctionPreCacher(x * 2, count, &f)())
        << std::move(FunctionPreCacher(x, count * 2, &f)())
        << std::move(FunctionPreCacher(x * 2, count * 2, &f)());
    std::cout << cnt;

    return 0;
}
