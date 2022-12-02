#include <iostream>
#include <fstream>
#include <vector>

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

    int32_t top3[3] = {};
    for (auto calories : elfCalories) {
        for (size_t i = 0; i < 3; i++) {
            if (calories > top3[i]) {
                for (size_t j = 2; j > i; j--) 
                    top3[j] = top3[j - 1];

                top3[i] = calories;
                break;
            }
        }
    }

    std::cout << top3[0] + top3[1] + top3[2] << "\n";
}