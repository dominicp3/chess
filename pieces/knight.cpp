#include "knight.h"

Knight::Knight(char colour, int x, int y): Piece('n', colour, x, y)
{
        if (colour == 'w') {
                m_icon = QPixmap(QDir::currentPath().append("/images/knight_white.png"));
        } else if (colour == 'b') {
                m_icon = QPixmap(QDir::currentPath().append("/images/knight_black.png"));
        }
}

std::vector<std::pair<int, int>> Knight::legal_moves(Board &board)
{
        if (m_x < 0 or m_x >= 8 or m_y < 0 or m_y >= 8) {
                return {};
        }

        std::vector<std::pair<int, int>> moves;

        int x = m_x;
        int y = m_y;

        // left
        if (x - 2 >= 0 and y - 1 >= 0) {
                if (board[x - 2][y - 1] == nullptr) {
                         moves.push_back({x - 2, y - 1});
                } else if (m_colour != board[x - 2][y - 1]->colour()) {
                        moves.push_back({x - 2, y - 1});
                }
        }

        if (x - 2 >= 0 and y + 1 < 8) {
                if (board[x - 2][y + 1] == nullptr) {
                         moves.push_back({x - 2, y + 1});
                } else if (m_colour != board[x - 2][y + 1]->colour()) {
                        moves.push_back({x - 2, y + 1});
                }
        }

        // top
        if (x - 1 >= 0 and y + 2 < 8) {
                if (board[x - 1][y +2] == nullptr) {
                         moves.push_back({x - 1, y + 2});
                } else if (m_colour != board[x - 1][y + 2]->colour()) {
                        moves.push_back({x - 1, y + 2});
                }
        }

        if (x + 1 < 8 and y + 2 < 8) {
                if (board[x + 1][y + 2] == nullptr) {
                         moves.push_back({x + 1, y + 2});
                } else if (m_colour != board[x + 1][y + 2]->colour()) {
                        moves.push_back({x + 1, y + 2});
                }
        }

        // right
        if (x + 2 < 8 and y - 1 >= 0) {
                if (board[x + 2][y - 1] == nullptr) {
                         moves.push_back({x + 2, y - 1});
                } else if (m_colour != board[x + 2][y - 1]->colour()) {
                        moves.push_back({x + 2, y - 1});
                }
        }

        if (x + 2 < 8 and y + 1 < 8) {
                if (board[x + 2][y + 1] == nullptr) {
                         moves.push_back({x + 2, y + 1});
                } else if (m_colour != board[x + 2][y + 1]->colour()) {
                        moves.push_back({x + 2, y + 1});
                }
        }

        // bottom
        if (x - 1 >= 0 and y - 2 >= 0) {
                if (board[x - 1][y - 2] == nullptr) {
                         moves.push_back({x - 1, y - 2});
                } else if (m_colour != board[x - 1][y - 2]->colour()) {
                        moves.push_back({x - 1, y - 2});
                }
        }

        if (x + 1 < 8 and y - 2 >= 0) {
                if (board[x + 1][y - 2] == nullptr) {
                         moves.push_back({x + 1, y - 2});
                } else if (m_colour != board[x + 1][y - 2]->colour()) {
                        moves.push_back({x + 1, y - 2});
                }
        }

        return moves;
}
