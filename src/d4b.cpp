#include <iostream>
#include <fstream>

int main()
{
    std::ifstream assignments("inputs/d4.txt");
    std::string assignmentPair;
    int32_t range1[2], range2[2];
    int32_t overlap = 0;

    while (assignments >> assignmentPair) {
        range1[0] = stoi(assignmentPair.substr(0, assignmentPair.find('-')));
        assignmentPair.erase(0, assignmentPair.find('-') + 1);
        range1[1] = stoi(assignmentPair.substr(0, assignmentPair.find(',')));
        assignmentPair.erase(0, assignmentPair.find(',') + 1);
        range2[0] = stoi(assignmentPair.substr(0, assignmentPair.find('-')));
        assignmentPair.erase(0, assignmentPair.find('-') + 1);
        range2[1] = stoi(assignmentPair);

        if (range1[0] <= range2[0]) {
            if (range1[1] <= range2[1] && range1[1] >= range2[0]) overlap++;
            else if (range1[1] >= range2[1]) overlap++;
        }
        else if (range2[0] <= range1[0]) {
            if (range2[1] <= range1[1] && range2[1] >= range1[0]) overlap++;
            else if (range2[1] >= range1[1]) overlap++;
        }
    }

    std::cout << "Total overlapping assignments: " << overlap << "\n";
}