#include <iostream>
#include <fstream>

int main()
{
    std::ifstream rucksacks("inputs/d3.txt");
    std::string rucksack, compartment[2], similarItem;
    int32_t totalScore = 0;

    while (rucksacks >> rucksack) {
        compartment[0] = rucksack.substr(0, rucksack.length()/2);
        compartment[1] = rucksack.substr(rucksack.length()/2);

        for (auto item : compartment[0]) {
            auto similarLocation = compartment[1].find(item);
            if (similarLocation != std::string::npos) {
                similarItem = compartment[1].substr(similarLocation, 1);
                break;
            }
        }

        if (similarItem[0] >= 'a') {
            totalScore += similarItem[0] - 'a' + 1;
            continue;
        }
        totalScore += similarItem[0] - 'A' + 1 + 26;
    }

    std::cout << "Total Score: " << totalScore << "\n";
}