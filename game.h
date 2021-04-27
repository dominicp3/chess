#pragma once

#include "board.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include <limits>
#include <QPainter>
#include <algorithm>
#include <memory>

class Game
{
public:
        Game();
        void render(QPainter& paint);
        void select_square(int x, int y);

        std::vector<std::shared_ptr<Board>> actions(Board& board, char player);
        void next_move();
        int minimax(std::shared_ptr<Board> node, int depth, int alpha, int beta, char player);
private:
        Board m_board;
        char m_colour_to_play = 'w';

        // currently selected square (mouse input)
        int m_x;
        int m_y;

        std::vector<std::pair<int, int>> m_circled_squares;
};
