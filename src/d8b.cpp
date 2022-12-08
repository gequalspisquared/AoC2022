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

    size_t largestScenicScore = 0;

    for (size_t r = 0; r < numRows; r++) {
        for (size_t c = 0; c < numCols; c++) {
            size_t currentHeight = trees[r][c];
            size_t visibleAbove = 0;
            for (int32_t ro = r - 1; ro >= 0; ro--) { // above
                visibleAbove++;
                if (trees[ro][c] >= currentHeight)
                    break;
            }

            size_t visibleBelow = 0;
            for (int32_t ro = r + 1; ro < numRows; ro++) { // below
                visibleBelow++;
                if (trees[ro][c] >= currentHeight)
                    break;
            }

            size_t visibleLeft = 0;
            for (int32_t co = c - 1; co >= 0; co--) { // left
                visibleLeft++;
                if (trees[r][co] >= currentHeight)
                    break;
            }

            size_t visibleRight = 0;
            for (int32_t co = c + 1; co < numCols; co++) { // right
                visibleRight++;
                if (trees[r][co] >= currentHeight)
                    break;
            }

            size_t scenicScore = visibleAbove*visibleBelow*visibleLeft*visibleRight;
            largestScenicScore = (scenicScore > largestScenicScore) ? scenicScore : largestScenicScore;
        }
    }

    std::cout << "Largest scenic score: " << largestScenicScore << "\n";
}