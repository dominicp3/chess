#pragma once

#include "piece.h"

class Pawn : public Piece
{
public:
        Pawn(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
};
