#pragma once

#include "board.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include <QPainter>

class Game
{
public:
        Game(char colourTurn = 'w');
        void playGame(); // empty function
        void render(QPainter &paint);
        void select_square(int x, int y);
        std::vector<std::pair<int, int>> legal_moves(int x, int y);
private:
        Board m_board;
        char m_colour_to_play;

        // currently selected square (mouse input)
        int m_x;
        int m_y;

        std::vector<std::pair<int, int>> m_circled_squares;
};
