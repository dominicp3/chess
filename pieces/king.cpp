#include "king.h"

King::King(char colour, int x, int y): Piece('k', colour, x, y)
{
        if (colour == 'w') {
                m_icon = QPixmap(QDir::currentPath().append("/images/king_white.png"));
        } else if (colour == 'b') {
                m_icon = QPixmap(QDir::currentPath().append("/images/king_black.png"));
        }
}

std::vector<std::pair<int, int>> King::legal_moves(Board &board)
{
        if (m_x < 0 or m_x >= 8 or m_y < 0 or m_y >= 8) {
                return {};
        }

        std::vector<std::pair<int, int>> moves;

        int x;
        int y;

        x = m_x + 1;
        y = m_y;
        if (x < 8) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x + 1;
        y = m_y - 1;
        if (x < 8 and y >= 0) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x;
        y = m_y - 1;
        if (y >= 0) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x - 1;
        y = m_y - 1;
        if (x >= 0 and y >= 0) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x - 1;
        y = m_y;
        if (x >= 0) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x - 1;
        y = m_y + 1;
        if (x >= 0 and y < 8) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x;
        y = m_y + 1;
        if (y < 8) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        x = m_x + 1;
        y = m_y + 1;
        if (x < 8 and y < 8) {
                if (board[x][y] == nullptr or board[x][y]->colour() != m_colour) {
                        moves.push_back({x, y});
                }
        }

        return moves;
}
