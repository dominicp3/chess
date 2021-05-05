#ifndef ENGINE_H
#define ENGINE_H

#include "gamestate.h"
#include "piecemove.h"
#include <limits>
#include <vector>
#include <memory>
#include <unordered_map>

class Engine
{
public:
        Engine();

        std::unique_ptr<GameState> next_move(GameState& board);

private:
        std::vector<std::unique_ptr<GameState>> actions(GameState& board);
        int minimax(GameState& node, int depth, int alpha, int beta);
        int evaluate(GameState& board);

        PieceMove piece_move;

        std::unordered_map<char, int> piece_value =
        {
                {'p', 1}, {'P', -1},
                {'n', 3}, {'N', -3},
                {'b', 3}, {'B', -3},
                {'r', 5}, {'R', -5},
                {'q', 9}, {'Q', -9}
        };
};

#endif // ENGINE_H
