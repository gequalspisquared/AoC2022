#include <iostream>
#include <fstream>

int main()
{
    std::ifstream moves("inputs/d2.txt");
    char enemyChoice, playerChoice;
    int32_t enemy, player;
    int32_t score = 0;

    while (moves >> enemyChoice) {
        moves >> playerChoice;
        player = (int)(playerChoice - 'X') + 1;
        enemy  = (int)(enemyChoice - 'A') + 1;

        score += player;
        if (player == enemy) {                       // draw
            score += 3;
            continue;
        }
        if (player - 3*(player == 3) + 1 == enemy) { // lose
            continue;
        }
        score += 6;                                  // win
    }

    std::cout << "Final score: " << score << "\n";
}