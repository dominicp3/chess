#pragma once

#include "piece.h"

class Board;

class Knight : public Piece
{
public:
        Knight(char colour, int x, int y);
        std::vector<std::pair<int, int>> legal_moves(Board &board);
};
