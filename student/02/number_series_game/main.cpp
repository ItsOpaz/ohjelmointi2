#include <iostream>


int main()
{
    int n;
    int counter;
    counter=1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> n;
    while(n>=counter){
        std::cout << counter << std::endl;
        counter = counter +1;

    }

}
