#include "board.h"
#include "pieces/piece.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

Board::Board(std::vector<Piece*> white, std::vector<Piece*> black): m_white_pieces(white), m_black_pieces(black)
{
        setup_board(white, black);
}

Board::~Board()
{
        for (auto& x : m_white_pieces) {
                delete x;
        }

        for (auto& x : m_black_pieces) {
                delete x;
        }
}

void Board::setup_board(std::vector<Piece*> white, std::vector<Piece*> black)
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

        for (Piece* p : white) {
                if (p->type() == 'k') {
                        m_white_king = p;
                }
                if (0 <= p->x() and p->x() < 8 and 0 <= p->y() and p->y() < 8) {
                        m_board[p->x()][p->y()] = p;
                }
        }

        for (Piece* p : black) {
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
                case 'q': m_white_pieces.push_back(new Queen(w->colour(), w->x(), w->y()));
                          break;
                case 'r': m_white_pieces.push_back(new Rook(w->colour(), w->x(), w->y()));
                          break;
                case 'n': m_white_pieces.push_back(new Knight(w->colour(), w->x(), w->y()));
                          break;
                case 'b': m_white_pieces.push_back(new Bishop(w->colour(), w->x(), w->y()));
                          break;
                case 'k': m_white_pieces.push_back(new King(w->colour(), w->x(), w->y()));
                          break;
                case 'p': m_white_pieces.push_back(new Pawn(w->colour(), w->x(), w->y()));
                          break;
                default: break;
                }
        }

        for (auto& b : board.m_black_pieces) {
                switch (b->type()) {
                case 'q': m_black_pieces.push_back(new Queen(b->colour(), b->x(), b->y()));
                          break;
                case 'r': m_black_pieces.push_back(new Rook(b->colour(), b->x(), b->y()));
                          break;
                case 'n': m_black_pieces.push_back(new Knight(b->colour(), b->x(), b->y()));
                          break;
                case 'b': m_black_pieces.push_back(new Bishop(b->colour(), b->x(), b->y()));
                          break;
                case 'k': m_black_pieces.push_back(new King(b->colour(), b->x(), b->y()));
                          break;
                case 'p': m_black_pieces.push_back(new Pawn(b->colour(), b->x(), b->y()));
                          break;
                default: break;
                }
        }

        setup_board(m_white_pieces, m_black_pieces);
}

char Board::check()
{
        for (Piece *black_piece : m_black_pieces) {
                if (black_piece->type() == 'k') {
                        if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() + 1 == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() - 1 == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() - 1 == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                return 'w';
                        } else if (black_piece->x() == m_white_king->x() and black_piece->y() + 1 == m_white_king->y()) {
                                return 'w';
                        }
                        continue;
                }
                for (std::pair<int, int>& xy : black_piece->legal_moves(*this)) {
                        if (xy.first == m_white_king->x() and xy.second == m_white_king->y()) {
                                return 'w';
                        }
                }
        }

        for (Piece* white_piece : m_white_pieces) {
                if (white_piece->type() == 'k') {
                        if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() + 1 == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() - 1 == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() - 1 == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                return 'b';
                        } else if (white_piece->x() == m_white_king->x() and white_piece->y() + 1 == m_white_king->y()) {
                                return 'b';
                        }
                        continue;
                }
                for (std::pair<int, int>& xy : white_piece->legal_moves(*this)) {
                        if (xy.first == m_black_king->x() and xy.second == m_black_king->y()) {
                                return 'b';
                        }
                }
        }

        return 0;
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

        return white_value - black_value;
}

void Board::move_piece(int old_x, int old_y, int new_x, int new_y)
{
        if (m_board[new_x][new_y] != nullptr) {
                m_board[new_x][new_y]->set_position(-1, -1);
        }

//      EN PASSANT
        if (m_board[old_x][old_y]->type() == 'p') {
                if ((new_x - old_x == 1 or new_x - old_x == -1) and m_board[new_x][new_y] == nullptr) {
                        if (m_board[old_x][old_y]->colour() == 'w') {
                                m_board[new_x][new_y - 1]->set_position(-1, -1);
                                m_board[new_x][new_y - 1] = nullptr;
                        }

                        if (m_board[old_x][old_y]->colour() == 'b') {
                                m_board[new_x][new_y + 1]->set_position(-1, -1);
                                m_board[new_x][new_y + 1] = nullptr;
                        }
                }
        }

        m_board[new_x][new_y] = m_board[old_x][old_y];
        m_board[old_x][old_y] = nullptr;
        m_board[new_x][new_y]->set_position(new_x, new_y);

//      PAWN BEING PROMOTED TO QUEEN
        if (m_board[new_x][new_y]->type() == 'p' and (new_y == 7 or new_y == 0)) {
                m_board[new_x][new_y]->set_position(-1, -1);
                add_piece(new Queen(m_board[new_x][new_y]->colour(), new_x, new_y));
        }

        if (m_board[new_x][new_y]->type() == 'r' or m_board[new_x][new_y]->type() == 'k') {
                m_board[new_x][new_y]->set_aux();
        }

        if (m_board[new_x][new_y]->type() == 'p') {
                if (old_y == 1 and new_y == 3) {
                        m_board[new_x][new_y]->set_aux();
                }

                if (old_y == 6 and new_y == 4) {
                        m_board[new_x][new_y]->set_aux();
                }
        }

//      CASTLING
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

void Board::add_piece(Piece *p)
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

std::vector<Piece*>& Board::operator[](int index)
{
        return m_board[index];
}
