#ifndef COMPUTER_H
#define COMPUTER_H

#include "gamestate.h"
#include <vector>
#include <memory>

class Computer
{
public:
        Computer();

        std::vector<std::shared_ptr<GameState>> actions(GameState& board, char player);
        void next_move();
        int minimax(std::shared_ptr<GameState> node, int depth, int alpha, int beta, char player);
};

#endif // COMPUTER_H
