#include <iostream>
#include <fstream>

int main()
{
    std::ifstream datastream("inputs/d6.txt");
    std::string message = "";
    size_t count = 0;
    char c;

    while (datastream >> std::noskipws >> c && message.size() != 14) {
        count++;
        size_t duplicate = message.find(c);
        message.push_back(c);
        if (duplicate != std::string::npos) 
            message = message.substr(duplicate + 1);
    }
    std::cout << count << "\n";
}