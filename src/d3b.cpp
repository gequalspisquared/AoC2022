#include <iostream>
#include <fstream>

int main()
{
    std::ifstream rucksacks("inputs/d3.txt");
    std::string rucksack[3], similarItem;
    int32_t totalScore = 0;

    while (rucksacks >> rucksack[0] >> rucksack[1] >> rucksack[2]) {
        for (auto item : rucksack[0]) {
            auto similarLocation = rucksack[1].find(item);
            if (similarLocation != std::string::npos) {
                similarLocation = rucksack[2].find(item);
                if (similarLocation != std::string::npos) {
                    similarItem = rucksack[2].substr(similarLocation, 1);
                    break;
                }
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