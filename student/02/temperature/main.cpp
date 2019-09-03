#include <iostream>

int main()
{
    std::cout << "Enter a temperature: ";

    // Write your code here
    int temperature;
    std::cin >> temperature;
    std::cout << temperature;
    std::cout << " degrees Celsius is ";
    std::cout << temperature * 1.8 + 32;
    std::cout << " degrees Fahrenheit" << std::endl;
    std::cout << temperature;
    std::cout << " degrees Fahrenheit is ";
    std::cout << (temperature - 32)/1.8;
    std::cout << " degrees Celsius" << std::endl;

    return 0;
}
