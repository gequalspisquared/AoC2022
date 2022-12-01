
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream calorieFile("inputs/d1.txt");
    std::string calories;
    std::vector<int32_t> elfCalories;
    int32_t currentElfCalories = 0;

    while (getline(calorieFile, calories)) {
        if (calories.empty()) {
            elfCalories.push_back(currentElfCalories);
            currentElfCalories = 0;
            continue;
        }

        currentElfCalories += stoi(calories);
    }
    elfCalories.push_back(currentElfCalories);

    std::cout << *std::max_element(elfCalories.begin(), elfCalories.end()) 
              << "\n";
}