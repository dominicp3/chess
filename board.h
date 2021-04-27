#pragma once

#include <QPainter>
#include <vector>
#include <memory>

class Piece;

class Board
{
public:
        Board(const std::list<std::shared_ptr<Piece>>& white = {}, const std::list<std::shared_ptr<Piece>>& black = {});
        Board(const Board& b);

        /*
         * returns:
         *      'w' if white is in check/checkmate
         *      'b' if black is in check/checkmate
         *       0  otherwise
         */
        bool check(char player);
        bool checkmate(char player);

        int evaluate();

        void move_piece(int old_x, int old_y, int new_x, int new_y);
        void render(QPainter& paint);
        void add_piece(std::shared_ptr<Piece> p);
        void remove_piece(int x, int y);

        std::vector<std::pair<int, int>> legal_moves(int x, int y);

        std::list<std::shared_ptr<Piece>>& get_white_pieces() {return m_white_pieces;}
        std::list<std::shared_ptr<Piece>>& get_black_pieces() {return m_black_pieces;}
        void print_board();

        std::vector<std::shared_ptr<Piece>>& operator[](int index);
private:
        void setup_board(std::list<std::shared_ptr<Piece>> white, std::list<std::shared_ptr<Piece>> black);

        std::vector<std::vector<std::shared_ptr<Piece>>> m_board;

        std::list<std::shared_ptr<Piece>> m_white_pieces;
        std::list<std::shared_ptr<Piece>> m_black_pieces;

        std::shared_ptr<Piece> m_white_king;
        std::shared_ptr<Piece> m_black_king;
};
