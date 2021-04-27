#pragma once

#include "piece.h"

class Rook : public Piece
{
public:
        Rook(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
        bool moved = false;
};
