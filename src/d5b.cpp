#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void move(size_t num, std::vector<char> &fromStack, std::vector<char> &toStack)
{
    size_t size = fromStack.size();
    for (size_t i = num; i > 0; i--) 
        toStack.push_back(fromStack[size - i]);
    for (size_t i = 0; i < num; i++) 
        fromStack.pop_back();
}

int main()
{
    const size_t numStacks = 9;
    std::ifstream cratesFile("inputs/d5.txt");
    std::string cratesLine;
    std::vector<char> crates[numStacks];

    while (getline(cratesFile, cratesLine)) {
        if (cratesLine.substr(1, 1) == "1") break;
        for (size_t i = 0; i < numStacks; i++) {
            if (cratesLine.substr(4*i + 1, 1) == " ") continue;
            crates[i].push_back(cratesLine[4*i + 1]);
        }
    }

    for (size_t i = 0; i < numStacks; i++)
        std::reverse(crates[i].begin(), crates[i].end());
    
    size_t num, from, to;
    std::string blank;
    while (cratesFile >> blank >> num >> blank >> from >> blank >> to) {
        move(num, crates[from - 1], crates[to - 1]);
    }

    for (size_t i = 0; i < numStacks; i++)
        std::cout << crates[i].back();
    std::cout << "\n";
}