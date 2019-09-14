#include <iostream>
#include <cmath>

int main()
{
    int value;
    int result;
    std::cout << "Enter a number: ";
    std::cin >> value;
    result = pow(value,3);
    if (result<0){
        std::cout <<"Error! The cube of ";
        std::cout <<value;
        std::cout << " is not ";
        std::cout << result << std::endl;
    }
    else if(value != pow(result, 1/3)){
        std::cout <<"Error! The cube of ";
        std::cout <<value;
        std::cout << " is not ";
        std::cout << result << std::endl;
    }
    else{
    std::cout <<"The cube of ";
    std::cout << value;
    std::cout <<" is ";
    std::cout << result << std::endl;
    }
}
