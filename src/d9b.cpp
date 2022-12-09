#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

template<typename T>
T mag(T x) 
{
    return (x < 0) ? -x : x;
}

void moveTail(const int32_t *head, int32_t *tail)
{
    int32_t dx = head[0] - tail[0];
    int32_t dy = head[1] - tail[1];

    if (dx == 0 && mag<int32_t>(dy) == 2) {
        tail[1] += dy/2;
        return;
    }
    if (mag<int32_t>(dx) == 2 && dy == 0) {
        tail[0] += dx/2;
        return;
    }
    if (mag<int32_t>(dx) > 1 || mag<int32_t>(dy) > 1) {
        tail[0] += (dx > 0) ? 1 : -1; 
        tail[1] += (dy > 0) ? 1 : -1;
    }
}

int main()
{
    const int tailLen = 9;
    const int tailInd = tailLen - 1;
    std::ifstream movesFile("inputs/d9.txt");
    char headDirection;
    size_t headDistance;
    int32_t stepDirection[] = {0, 0};
    int32_t head[] = {0, 0}; // (x, y)
    int32_t tail[tailLen][2] = {};
    std::vector<std::array<int32_t, 2>> positionsVisited;

    while (movesFile >> headDirection) {
        stepDirection[0] = 0; stepDirection[1] = 0;
        if      (headDirection == 'U') stepDirection[1] =  1;
        else if (headDirection == 'R') stepDirection[0] =  1;
        else if (headDirection == 'D') stepDirection[1] = -1;
        else                           stepDirection[0] = -1;

        movesFile >> headDistance;
        for (size_t i = 0; i < headDistance; i++) {
            positionsVisited.push_back(std::array<int32_t, 2> {tail[tailInd][0], tail[tailInd][1]});
            head[0] += stepDirection[0]; head[1] += stepDirection[1];
            moveTail(head, tail[0]);
            for (size_t j = 1; j < tailLen; j++)
                moveTail(tail[j - 1], tail[j]);
        }
    }
    positionsVisited.push_back(std::array<int32_t, 2> {tail[tailInd][0], tail[tailInd][1]});

    std::cout << "Final Tail Position: (" << tail[tailInd][0] << ", " << tail[tailInd][1] << ")\n";
    std::sort(positionsVisited.begin(), positionsVisited.end());
    size_t uniquePositions = std::unique(positionsVisited.begin(), positionsVisited.end()) - positionsVisited.begin();
    std::cout << "Number of unique positions visited: "  << uniquePositions << "\n";
}