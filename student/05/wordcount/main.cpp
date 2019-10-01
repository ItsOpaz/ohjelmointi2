#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <iterator>

std::vector<std::string> split(std::string str){
    std::vector<std::string>result;
    while(str.size()){
        unsigned long int index = str.find(" ");
        unsigned long int a = std::string::npos;
        if(index!= a){
            result.push_back(str.substr(0,index));
            str = str.substr(index+1);
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
        int b = (result.size());
        std::vector <std::string> withoutspaces;
        for(int i=0; i<b; ++i){
            std::string word = result.at(i);
            if(word == ""){
            }else{
                withoutspaces.push_back(result.at(i));
            }
        }
        return withoutspaces;
}
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
    int i = 1;
    std::map<int, std::vector<std::string>> lines;
    std::vector<std::string> a;
    std::vector<std::string> words;
    std::string row;
    while (getline(file, row)){
        std::vector<std::string> line_as_vector = split(row);
        lines.insert({i,line_as_vector});
        ++i;
        a.insert(std::end(a), std::begin(line_as_vector), std::end(line_as_vector));
    }
    for (std::string elem:a){
        if (std::find(words.begin(), words.end(), elem) != words.end() ){
            continue;
        }else{
            words.push_back(elem);
            std::sort(words.begin(), words.end());
        }
    }
    for (std::string elem : words){
        std::vector<int> rows;
        for (auto line : lines){
            std::vector<std::string> verse = line.second;
            if (std::find(verse.begin(), verse.end(), elem) != verse.end()){
                continue;
            }else{
                rows.push_back(line.first);
            }
        }
        std::stringstream result;
        std::copy(rows.begin(), rows.end(), std::ostream_iterator<int>(result, ", "));
        std::string s = result.str();
            s = s.substr(0, s.length()-2);
        std::cout << elem << rows.size() << s <<std::endl;
    }
}
