#include <iostream>
#include <fstream>

int32_t signalStrength(size_t cycle, int32_t registerX)
{
    return (cycle + 20)%40 == 0 ? registerX*cycle : 0;
}

void draw(int32_t registerX)
{
    static size_t pixel = 0;
    int32_t dx = registerX - pixel;

    if ((dx < 0 ? -dx : dx) <= 1)
        std::cout << "#";
    else 
        std::cout << ".";
    pixel++;
    
    if (pixel%40 == 0) {
        std::cout << "\n";
        pixel = 0;
    }
}

int main()
{
    std::ifstream instructionsFile("inputs/d10.txt");
    std::string instruction;
    int32_t V = 0;
    int32_t X = 1;
    bool add = false;
    size_t cycle = 1;
    size_t totalStrength = 0;

    while (instructionsFile >> instruction) {
        totalStrength += signalStrength(cycle, X);
        draw(X);
        if (instruction == "addx") add = true;
        cycle++;

        if (add) {
            totalStrength += signalStrength(cycle, X);
            draw(X);
            instructionsFile >> V;
            X += V;
            cycle++;
            add = false;
        }
    }

    std::cout << totalStrength << "\n";
}