#pragma once

#include "piece.h"

class Queen : public Piece
{
public:
        Queen(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
};
