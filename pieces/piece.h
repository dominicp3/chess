#pragma once

#include <QPainter>
#include <QDir>

#include "board.h"

class Board;

class Piece
{
public:
        Piece(char type, char colour, int x, int y);
        virtual ~Piece() {}

        virtual void set_position(int x, int y);
        virtual int x();
        virtual int y();
        virtual void render(QPainter &paint);

        virtual std::vector<std::pair<int, int>> legal_moves(Board &board) = 0;
        virtual char colour() {return m_colour;}
        virtual char type() {return m_type;}
        bool is_valid_coord() {return 0 <= m_x and m_x < 8 and 0 <= m_y and m_y < 8;}

protected:
        char m_type;  // 'p' = pawn, 'r' = rook, 'b' = bishop, 'k' = king, 'n' = knight, 'q' = queen
        char m_colour; // 'w' = white, 'b' = black
        int m_x;
        int m_y;
        QPixmap m_icon;
};
