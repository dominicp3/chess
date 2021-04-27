#include "pawn.h"

Pawn::Pawn(char colour, int x, int y): Piece('p', colour, x, y)
{
        if (colour == 'w') {
                m_icon = QPixmap(QDir::currentPath().append("/images/pawn_white.png"));
        } else if (colour == 'b'){
                m_icon = QPixmap(QDir::currentPath().append("/images/pawn_black.png"));
        }
}

std::vector<std::pair<int, int>> Pawn::legal_moves(Board &board)
{
        if (m_x < 0 or m_x >= 8 or m_y < 0 or m_y >= 8) {
                return {};
        }

        std::vector<std::pair<int, int>> moves;

        int x = m_x;
        int y = m_y;

        if (m_colour == 'w') {
                if (y == 1 and board[x][y + 1] == nullptr and board[x][y + 2] == nullptr) {
                        moves.push_back({x, y + 1});
                        moves.push_back({x, y + 2});
                } else if (y + 1 < 8 and board[x][y + 1] == nullptr) {
                        moves.push_back({x, y + 1});
                }

                if (x + 1 < 8 and y + 1 < 8 and board[x + 1][y + 1] != nullptr) {
                        if (m_colour != board[x + 1][y + 1]->colour()) {
                                moves.push_back({x + 1, y + 1});
                        }
                }

                if (x - 1 >= 0 and y + 1 < 8 and board[x - 1][y + 1] != nullptr) {
                        if (m_colour != board[x - 1][y + 1]->colour()) {
                                moves.push_back({x - 1, y + 1});
                        }
                }
        }

        if (m_colour == 'b') {
                if (y == 6 and board[x][y - 1] == nullptr and board[x][y - 2] == nullptr) {
                        moves.push_back({x, y - 1});
                        moves.push_back({x, y - 2});
                } else if (y - 1 >= 0 and board[x][y - 1] == nullptr) {
                        moves.push_back({x, y - 1});
                }

                if (x + 1 < 8 and y - 1 >= 0 and board[x + 1][y - 1] != nullptr) {
                        if (m_colour != board[x + 1][y - 1]->colour()) {
                                moves.push_back({x + 1, y - 1});
                        }
                }

                if (x - 1 >= 0 and y - 1 >= 0 and board[x - 1][y - 1] != nullptr) {
                        if (m_colour != board[x - 1][y - 1]->colour()) {
                                moves.push_back({x - 1, y - 1});
                        }
                }
        }

 //     En Passant
        if (m_colour == 'w') {
                if (m_y == 4) {
                        if (m_x + 1 < 8 and board[m_x+1][4] != nullptr
                                        and board[m_x+1][4]->type() == 'p'
                                        and board[m_x+1][4]->colour() == 'b'
                                        and board[m_x+1][4]->get_aux()) {
                                moves.push_back({x + 1, y + 1});
                        }

                        if (m_x - 1 >= 0 and board[m_x-1][4] != nullptr
                                        and board[m_x-1][4]->type() == 'p'
                                        and board[m_x-1][4]->colour() == 'b'
                                        and board[m_x-1][4]->get_aux()) {
                                moves.push_back({x - 1, y + 1});
                        }
                }
        }

        if (m_colour == 'b') {
                if (m_y == 3) {
                        if (m_x + 1 < 8 and board[m_x+1][3] != nullptr
                                        and board[m_x+1][3]->type() == 'p'
                                        and board[m_x+1][3]->colour() == 'w'
                                        and board[m_x+1][3]->get_aux()) {
                                moves.push_back({x + 1, y - 1});
                        }

                        if (m_x - 1 >= 0 and board[m_x-1][3] != nullptr
                                        and board[m_x-1][3]->type() == 'p'
                                        and board[m_x-1][3]->colour() == 'w'
                                        and board[m_x-1][3]->get_aux()) {
                                moves.push_back({x - 1, y - 1});
                        }
                }
        }

        return moves;
}
