#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include "gamestate.h"
#include <vector>
#include <memory>

namespace piecemove {
        std::vector<std::unique_ptr<GameState>> moves(GameState& board, int x, int y);
}

#endif // PIECEMOVE_H
