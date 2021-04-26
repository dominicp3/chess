﻿#include "bishop.h"

Bishop::Bishop(char colour, int x, int y): Piece('b', colour, x, y)
{
        if (colour == 'w') {
                m_icon = QPixmap(QDir::currentPath().append("/images/bishop_white.png"));
        } else if (colour == 'b') {
                m_icon = QPixmap(QDir::currentPath().append("/images/bishop_black.png"));
        }
}


std::vector<std::pair<int, int>> Bishop::legal_moves(Board &board)
{
        if (m_x < 0 or m_x >= 8 or m_y < 0 or m_y >= 8) {
                return {};
        }

        std::vector<std::pair<int, int>> moves;

        int x = m_x + 1;
        int y = m_y + 1;

        // top right
        while (x < 8 and y < 8) {
                if (board[x][y] != nullptr) {
                        if (m_colour != board[x][y]->colour()) {
                                moves.push_back({x, y});
                        }
                        break;
                } else {
                        moves.push_back({x, y});
                        x += 1;
                        y += 1;
                }
        }

        x = m_x - 1;
        y = m_y + 1;

        // top left
        while (x >= 0 and y < 8) {
                if (board[x][y] != nullptr) {
                        if (m_colour != board[x][y]->colour()) {
                                moves.push_back({x, y});
                        }
                        break;
                } else {
                        moves.push_back({x, y});
                        x -= 1;
                        y += 1;
                }
        }

        x = m_x - 1;
        y = m_y - 1;

        // bottom left
        while (x >= 0 and y >= 0) {
                if (board[x][y] != nullptr) {
                        if (m_colour != board[x][y]->colour()) {
                                moves.push_back({x, y});
                        }
                        break;
                } else {
                        moves.push_back({x, y});
                        x -= 1;
                        y -= 1;
                }
        }

        x = m_x + 1;
        y = m_y - 1;

        // bottom right
        while (x < 8 and y >= 0) {
                if (board[x][y] != nullptr) {
                        if (m_colour != board[x][y]->colour()) {
                                moves.push_back({x, y});
                        }
                        break;
                } else {
                        moves.push_back({x, y});
                        x += 1;
                        y -= 1;
                }
        }

        return moves;
}
