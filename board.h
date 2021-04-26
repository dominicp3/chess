#pragma once

#include <QPainter>
#include <vector>
#include <memory>

class Piece;

class Board
{
public:
        Board(std::vector<Piece*> white, std::vector<Piece*> black);
        ~Board();

        Board(const Board& b);

        char check();
        void move_piece(int old_x, int old_y, int new_x, int new_y);
        int evaluate();
        void render(QPainter &paint);
        void add_piece(Piece *p);

//        std::vector<std::vector<Piece*>> get_board() {return m_board;}

        std::vector<Piece*>& operator[](int index);
private:
        void setup_board(std::vector<Piece*> white, std::vector<Piece*> black);

        std::vector<std::vector<Piece*>> m_board;

        std::vector<Piece*> m_white_pieces;
        std::vector<Piece*> m_black_pieces;

        Piece* m_white_king;
        Piece* m_black_king;
};
