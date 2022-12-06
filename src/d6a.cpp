#include <iostream>
#include <fstream>

int main()
{
    std::ifstream datastream("inputs/d6.txt");
    std::string code = "";
    size_t count = 0;
    char c;

    while (datastream >> std::noskipws >> c && code.size() != 4) {
        count++;
        size_t duplicate = code.find(c);
        code.push_back(c);
        if (duplicate != std::string::npos) 
            code = code.substr(duplicate + 1);
    }
    std::cout << count << "\n";
}