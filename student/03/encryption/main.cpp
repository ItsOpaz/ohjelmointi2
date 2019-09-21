#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>

using namespace std;

int main()
{
    string line;
    string base = "abcdefghijklmnopqrstuvwzyx";
    cout << "Enter the encryption key: ";
    cin >> line;
    if (line.length()==26){
        for (int i=1; i < 26; i++){
            if (isupper(line.at(i))){
                cout << "Error! The encryption key must contain only lower case characters."<< endl;
                return EXIT_FAILURE;
            }
        }
        int j;
        int count[26] = {0};

        for(j=0;line[j]!='\0';j++){
        count[line[j]-'a']++;
        }
        for(j=0;j<26;j++){
            if(!count[j]){
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return EXIT_FAILURE;
            }
        }
        string encrypt;
        cout << "Enter the text to be encrypted: ";
        cin >> encrypt;
        for (int i=0; i < 26; i++){
            if (isupper(encrypt.at(i))){
                cout << "Error! The encryption key must contain only lower case characters."<< endl;
                return EXIT_FAILURE;
            }
        }
        int input_length;
        input_length = encrypt.length();
        int index;
        string crypted_text = encrypt;
        for (int i=0; i < input_length-1 ;++i ){
            index = base.find(encrypt.at(i));
            crypted_text.at(i) = line.at(index);
                }
        cout << "Encrypted text: " << crypted_text << endl;

    }else{
        cout << "Error! The encryption key must contain 26 characters."<< endl;
        return EXIT_FAILURE;
    }

}
