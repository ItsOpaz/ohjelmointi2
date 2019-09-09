#include <iostream>


int main()
{
    int n;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> n;
    for(int a=1; a<=n; a=a+1){
        if (a%3==0){
            if (a%7==0){
                std::cout << "zip boing" << std::endl;
            }else{
                std::cout << "zip" << std::endl;
            }
        }else if (a%7==0){
            std::cout << "boing" << std::endl;
        }else{
            std::cout << a << std::endl;
        }
    }

}
