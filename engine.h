#ifndef ENGINE_H
#define ENGINE_H

#include "gamestate.h"
#include "piecemove.h"
#include <limits>
#include <vector>
#include <memory>
#include <unordered_map>

namespace engine {
        std::unique_ptr<GameState> next_move(GameState& board);
}

#endif // ENGINE_H
