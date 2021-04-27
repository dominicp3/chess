#include "board.h"
#include "pieces/piece.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include <iostream>

Board::Board(const std::list<std::shared_ptr<Piece>>& white, const std::list<std::shared_ptr<Piece>>& black):
        m_white_pieces(white), m_black_pieces(black)
{
        setup_board(white, black);
}

void Board::setup_board(std::list<std::shared_ptr<Piece>> white, std::list<std::shared_ptr<Piece>> black)
{
        m_board = {
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

        for (auto& p : white) {
                if (p->type() == 'k') {
                        m_white_king = p;
                }
                if (0 <= p->x() and p->x() < 8 and 0 <= p->y() and p->y() < 8) {
                        m_board[p->x()][p->y()] = p;
                }
        }

        for (auto& p : black) {
                if (p->type() == 'k') {
                        m_black_king = p;
                }
                if (0 <= p->x() and p->x() < 8 and 0 <= p->y() and p->y() < 8) {
                        m_board[p->x()][p->y()] = p;
                }
        }
}

Board::Board(const Board& board)
{
        for (auto& w : board.m_white_pieces) {
                switch (w->type()) {
                case 'q': m_white_pieces.push_back(std::make_shared<Queen>(w->colour(), w->x(), w->y()));
                          break;
                case 'r': m_white_pieces.push_back(std::make_shared<Rook>(w->colour(), w->x(), w->y()));
                          break;
                case 'n': m_white_pieces.push_back(std::make_shared<Knight>(w->colour(), w->x(), w->y()));
                          break;
                case 'b': m_white_pieces.push_back(std::make_shared<Bishop>(w->colour(), w->x(), w->y()));
                          break;
                case 'k': m_white_pieces.push_back(std::make_shared<King>(w->colour(), w->x(), w->y()));
                          break;
                case 'p': m_white_pieces.push_back(std::make_shared<Pawn>(w->colour(), w->x(), w->y()));
                          break;
                default: break;
                }
        }

        for (auto& b : board.m_black_pieces) {
                switch (b->type()) {
                case 'q': m_black_pieces.push_back(std::make_shared<Queen>(b->colour(), b->x(), b->y()));
                          break;
                case 'r': m_black_pieces.push_back(std::make_shared<Rook>(b->colour(), b->x(), b->y()));
                          break;
                case 'n': m_black_pieces.push_back(std::make_shared<Knight>(b->colour(), b->x(), b->y()));
                          break;
                case 'b': m_black_pieces.push_back(std::make_shared<Bishop>(b->colour(), b->x(), b->y()));
                          break;
                case 'k': m_black_pieces.push_back(std::make_shared<King>(b->colour(), b->x(), b->y()));
                          break;
                case 'p': m_black_pieces.push_back(std::make_shared<Pawn>(b->colour(), b->x(), b->y()));
                          break;
                default: break;
                }
        }

        setup_board(m_white_pieces, m_black_pieces);
}

bool Board::check(char player)
{
        if (player == 'w') {
                for (auto& black_piece : m_black_pieces) {
                        if (black_piece->type() == 'k') {
                                if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                } else if (black_piece->x() == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                }
                                continue;
                        }
                        for (std::pair<int, int>& xy : black_piece->legal_moves(*this)) {
                                if (xy.first == m_white_king->x() and xy.second == m_white_king->y()) {
                                        return true;
                                }
                        }
                }
        }

        if (player == 'b') {
                for (auto& white_piece : m_white_pieces) {
                        if (white_piece->type() == 'k') {
                                if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                } else if (white_piece->x() == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                        return true;
                                }
                                continue;
                        }
                        for (std::pair<int, int>& xy : white_piece->legal_moves(*this)) {
                                if (xy.first == m_black_king->x() and xy.second == m_black_king->y()) {
                                        return true;
                                }
                        }
                }
        }

        return false;
}

bool Board::checkmate(char player)
{
        if (check(player)) {

                if (player == 'w') {
                        for (auto& p : m_black_pieces) {
                                for (auto m : p->legal_moves(*this)) {
                                        Board tmp = *this;
                                        tmp.move_piece(p->x(), p->y(), m.first, m.second);
                                        if (!tmp.check(player)) {
                                                return false;
                                        }
                                }
                        }
                }

                if (player == 'b') {
                        for (auto& p : m_white_pieces) {
                                for (auto m : p->legal_moves(*this)) {
                                        Board tmp = *this;
                                        tmp.move_piece(p->x(), p->y(), m.first, m.second);
                                        if (!tmp.check(player)) {
                                                return false;
                                        }
                                }
                        }
                }

        }

        return false;
}

void Board::move_piece(int old_x, int old_y, int new_x, int new_y)
{
//      EXECUTE EN PASSANT
        if (m_board[old_x][old_y]->type() == 'p') {
                if ((new_x - old_x == 1 or new_x - old_x == -1) and m_board[new_x][new_y] == nullptr) {
                        if (m_board[old_x][old_y]->colour() == 'w') {
                                remove_piece(new_x, new_y - 1);
                        }

                        if (m_board[old_x][old_y]->colour() == 'b') {
                                remove_piece(new_x, new_y + 1);
                        }
                }
        }

        if (m_board[new_x][new_y] != nullptr) {
                remove_piece(new_x, new_y);
        }

        m_board[new_x][new_y] = m_board[old_x][old_y];
        m_board[old_x][old_y] = nullptr;
        m_board[new_x][new_y]->set_position(new_x, new_y);

//      PAWN BEING PROMOTED TO QUEEN
        if (m_board[new_x][new_y]->type() == 'p' and (new_y == 7 or new_y == 0)) {
                remove_piece(new_x, new_y);
                add_piece(std::make_shared<Queen>(m_board[new_x][new_y]->colour(), new_x, new_y));
        }

//      IF ROOK OR KING IS MOVED, SET AUX FLAG TO PREVENT CASTLING
        if (m_board[new_x][new_y]->type() == 'r' or m_board[new_x][new_y]->type() == 'k') {
                m_board[new_x][new_y]->set_aux();
        }

//      SET EN PASSANT FLAG
        if (m_board[new_x][new_y]->type() == 'p') {
                if ((old_y == 1 and new_y == 3) or (old_y == 6 and new_y == 4)) {
                        if (new_x+1 < 8
                                and m_board[new_x+1][new_y] != nullptr
                                and m_board[new_x+1][new_y]->type() == 'p'
                                and m_board[new_x+1][new_y]->colour() != m_board[new_x][new_y]->colour())
                        {
                                m_board[new_x][new_y]->set_aux();
                        }

                        if (new_x-1 >= 0
                                and m_board[new_x-1][new_y] != nullptr
                                and m_board[new_x-1][new_y]->type() == 'p'
                                and m_board[new_x-1][new_y]->colour() != m_board[new_x][new_y]->colour())
                        {
                                m_board[new_x][new_y]->set_aux();
                        }
                }
        }

//      EXECUTE CASTLING
        if (m_board[new_x][new_y]->type() == 'k' and old_x == 4) {
                if (new_x == 2) {
                        m_board[3][new_y] = m_board[0][new_y];
                        m_board[0][new_y] = nullptr;
                        m_board[3][new_y]->set_position(3, new_y);
                }

                if (new_x == 6) {
                        m_board[5][new_y] = m_board[7][new_y];
                        m_board[7][new_y] = nullptr;
                        m_board[5][new_y]->set_position(5, new_y);
                }
        }
}

void Board::render(QPainter &paint)
{
        for (unsigned int i = 0; i < 8; i++) {
                for (unsigned int j = 0; j < 8; j++) {
                        if (m_board[i][j] != nullptr)
                                m_board[i][j]->render(paint);
                }
        }
}

void Board::add_piece(std::shared_ptr<Piece> p)
{
        if (p == nullptr) {
                return;
        }

        if (p->colour() == 'w') {
                m_white_pieces.push_back(p);
        }

        if (p->colour() == 'b') {
                m_black_pieces.push_back(p);
        }

        if (0 <= p->x() and p->x() < 8 and 0 <= p->y() and p->y() < 8) {
                m_board[p->x()][p->y()] = p;
        }
}

void Board::remove_piece(int x, int y)
{
        if (m_board[x][y]->colour() == 'w') {
                m_white_pieces.remove(m_board[x][y]);
        }

        if (m_board[x][y]->colour() == 'b') {
                m_black_pieces.remove(m_board[x][y]);
        }

        m_board[x][y] = nullptr;
}

std::vector<std::shared_ptr<Piece>>& Board::operator[](int index)
{
        return m_board[index];
}

std::vector<std::pair<int, int>> Board::legal_moves(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8 or m_board[x][y] == nullptr) {
                return {};
        }

        std::vector<std::pair<int, int>> moves = m_board[x][y]->legal_moves(*this);

        std::vector<std::pair<int, int>> possible_moves;

        for (std::pair<int, int> coord : moves) {
                Board tmp = Board(*this);
                tmp.move_piece(x, y, coord.first, coord.second);
                if (!tmp.check(m_board[x][y]->colour())) {
                        possible_moves.push_back({coord.first, coord.second});
                }
        }

        return possible_moves;
}

int Board::evaluate()
{
        int white_value = 0;
        int black_value = 0;

        for (auto p : m_white_pieces) {
                if (!p->is_valid_coord()) {
                        continue;
                }
                switch (p->type()) {
                case 'p': white_value += 1; break;
                case 'b': white_value += 3; break;
                case 'n': white_value += 3; break;
                case 'r': white_value += 5; break;
                case 'q': white_value += 9; break;
                default: break;
                }
        }

        for (auto p : m_black_pieces) {
                if (!p->is_valid_coord()) {
                        continue;
                }
                switch (p->type()) {
                case 'p': black_value += 1; break;
                case 'b': black_value += 3; break;
                case 'n': black_value += 3; break;
                case 'r': black_value += 5; break;
                case 'q': black_value += 9; break;
                default: break;
                }
        }

        if (checkmate('w')) {
                black_value += 1000;
        }

        if (checkmate('b')) {
                white_value += 1000;
        }

        return white_value - black_value;
}

void Board::print_board()
{
        for (int y = 7; y >= 0; y--) {
                std::string s = "|";
                if (m_board[0][y] != nullptr) {
                        s += m_board[0][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[1][y] != nullptr) {
                        s += m_board[1][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[2][y] != nullptr) {
                        s += m_board[2][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[3][y] != nullptr) {
                        s += m_board[3][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[4][y] != nullptr) {
                        s += m_board[4][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[5][y] != nullptr) {
                        s += m_board[5][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[6][y] != nullptr) {
                        s += m_board[6][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                if (m_board[7][y] != nullptr) {
                        s += m_board[7][y]->type();
                        s += "|";
                } else {
                        s += " |";
                }

                std::cout << s << std::endl;
        }

        std::cout << std::endl;
}

