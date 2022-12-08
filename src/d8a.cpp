#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream treesFile("inputs/d8.txt");
    std::vector<std::vector<uint32_t>> trees;
    std::vector<uint32_t> treesRow;
    char treeHeight;

    while (treesFile >> std::noskipws >> treeHeight) {
        if (treeHeight == '\n') {
            trees.push_back(treesRow);
            treesRow.clear();
            continue;
        }

        treesRow.push_back((uint32_t)(treeHeight - '0'));
    }
    trees.push_back(treesRow);

    size_t numRows = trees.size();
    size_t numCols = trees[0].size();

    std::vector<std::vector<bool>> visible(numRows, std::vector<bool>(numCols));

    for (size_t r = 0; r < numRows; r++) {
        for (size_t c = 0; c < numCols; c++) {
            if (r == 0 || r == numRows - 1 || c == 0 || c == numCols - 1) {
                visible[r][c] = true;
                continue;
            }

            size_t currentHeight = trees[r][c];
            bool isVisible = true;
            for (int32_t ro = r - 1; ro >= 0; ro--) // above
                if (trees[ro][c] >= currentHeight) {
                    isVisible = false;
                    break;
                }
            if (isVisible) {
                visible[r][c] = true;
                continue;
            }

            isVisible = true;
            for (int32_t ro = r + 1; ro < numRows; ro++) // below
                if (trees[ro][c] >= currentHeight) {
                    isVisible = false;
                    break;
                }
            if (isVisible) {
                visible[r][c] = true;
                continue;
            }

            isVisible = true;
            for (int32_t co = c - 1; co >= 0; co--) // left
                if (trees[r][co] >= currentHeight) {
                    isVisible = false;
                    break;
                }
            if (isVisible) {
                visible[r][c] = true;
                continue;
            }

            isVisible = true;
            for (int32_t co = c + 1; co < numCols; co++) // right
                if (trees[r][co] >= currentHeight) {
                    isVisible = false;
                    break;
                }
            if (isVisible) {
                visible[r][c] = true;
                continue;
            }
        }
    }

    size_t totalVisible = 0;
    for (size_t r = 0; r < numRows; r++)
        for (size_t c = 0; c < numCols; c++)
            totalVisible += visible[r][c];
    std::cout << "Total visible: " << totalVisible << "\n";
}