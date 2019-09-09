#include <iostream>

// Write here a function counting the mean value

int main()
{
    int a;
    int total = 0;
    int value;
    std::cout << "From how many integer numbers you want to count the mean value? ";
    std::cin >>a;
    if (a<=0){
        std::cout << "Cannot count mean value from ";
        std::cout << a;
        std::cout << " numbers" << std::endl;
    }else{
    for (int b=1;b<=a;b=b+1){
        std::cout << "Input ";
        std::cout << b;
        std::cout <<". number: ";
        std::cin >> value;
        total=total + value;
        
        }
    std::cout << "Mean value of the given numbers is ";
    std::cout << total/a << std::endl;
    }
}
