#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

int main()
{
    std::string inp;
    std::cout << "Input file: ";
    std::cin >> inp;
    std::ifstream file(inp);
    if ( not file ) {
        std::cout << "Error! The file " << inp << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::map<std::string, int> bongot;
    std::string rivi;
    while (getline(file, rivi)){
        int indeksi = rivi.find(":");
        int len = rivi.length();
        std::string name = rivi.substr(0,indeksi);
        std::string points_string = rivi.substr(indeksi+1,len-indeksi);
        int points = stoi(points_string);
        if ( bongot.find(name) != bongot.end() ) {
            bongot.at(name) += points;
        }
        bongot.insert({name, points});                       
    }
    std::cout << "Final scores:" << std::endl;
    for (auto elem : bongot){
        std::cout << elem.first << ": " << elem.second << std::endl;
    }
}
