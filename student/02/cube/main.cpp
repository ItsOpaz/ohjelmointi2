#include <iostream>
#include <cmath>

int main()
{
    int value;
    int result;
    int check;
    std::cout << "Enter a number: ";
    std::cin >> value;
    result = pow(value,3);
    check = pow(result,(float)1/3);
    if (result<0){
        std::cout <<"Error! The cube of ";
        std::cout <<value;
        std::cout << " is not ";
        std::cout << result;
        std::cout << "." << std::endl;
    }
    else if(value != check){
        std::cout <<"Error! The cube of ";
        std::cout <<value;
        std::cout << " is not ";
        std::cout << result;
        std::cout << "." << std::endl;
    }
    else{
        std::cout <<"The cube of ";
        std::cout << value;
        std::cout <<" is ";
        std::cout << result;
        std::cout << "." << std::endl;
    }
}
