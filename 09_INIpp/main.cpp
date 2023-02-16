#include "INIpp.hpp"

#include <iostream>
#include <sstream>

int main()
{
    INIpp::DOMParser parser;
    parser.AddFile("./config.ini");

    INIpp::DOM::Document doc = parser.Get();
    auto port = doc["owner"]["name"].Get<std::string>();
    std::cout << "Port: " << port;
}
