#pragma once

#include "piece.h"

class King : public Piece
{
public:
        King(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
        bool moved = false;
};
