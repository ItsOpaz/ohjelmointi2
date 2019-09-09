#include <iostream>


int main()
{
    int n;
    int counter;
    counter=1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> n;
    while(n>=counter){
        if (counter%3==0){
            std::cout << "zip" << std::endl;
            counter = counter +1;

        }
        std::cout << counter << std::endl;
        counter = counter +1;

    }

}
