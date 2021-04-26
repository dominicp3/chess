#pragma once

#include "piece.h"

class Bishop : public Piece
{
public:
        Bishop(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
};
