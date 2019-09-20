#include <iostream>

using namespace std;

bool check(int all_b,int drawn_b){
    if ((drawn_b < 0) or (all_b < 0)){
        cout << "The number of balls must be a positive number.";
        return false;
    }else if(drawn_b > all_b){
        cout << "The number of balls must be a positive number.";
        return false;
    }else{
        return true;
    }
}

int factorial(int value){
    unsigned long int factorial = 1;
    for(int i = 1; i <=value; ++i)
        {
            factorial *= i;
        }
    return factorial;
}

int propability(int all_b, int drawn_b){
    int divider;
    int difference = all_b - drawn_b;
    divider = factorial(all_b)/(factorial(difference)*factorial(drawn_b));
    return divider;
}

int main()
{
    int all_b;
    int drawn_b;
    cout << "Enter the total number of lottery balls: ";
    cin >> all_b;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_b;
    if (check(all_b,drawn_b) == true){
        cout << "The probability of guessing all " << drawn_b << " balls correctly is 1/"<<propability(all_b,drawn_b) << endl;;
    }else{
        return 0;
    }
}
