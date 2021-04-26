#include "game.h"
#include <iostream>

Game::Game(char colour_to_play):
        m_board({        // WHITE PIECES
                        new Rook('w', 0, 0),  new Knight('w', 1, 0),  new Bishop('w', 2, 0),  new King('w', 4, 0),
                        new Queen('w', 3, 0),  new Bishop('w', 5, 0),  new Knight('w', 6, 0),  new Rook('w', 7, 0),
                        new Pawn('w', 0, 1),  new Pawn('w', 1, 1),  new Pawn('w', 2, 1),  new Pawn('w', 3, 1),
                        new Pawn('w', 4, 1),  new Pawn('w', 5, 1),  new Pawn('w', 6, 1),  new Pawn('w', 7, 1)
              },

              {        // BLACK PIECES
                        new Rook('b', 0, 7),  new Knight('b', 1, 7),  new Bishop('b', 2, 7),  new King('b', 4, 7),
                        new Queen('b', 3, 7),  new Bishop('b', 5, 7),  new Knight('b', 6, 7),  new Rook('b', 7, 7),
                        new Pawn('b', 0, 6),  new Pawn('b', 1, 6),  new Pawn('b', 2, 6),  new Pawn('b', 3, 6),
                        new Pawn('b', 4, 6),  new Pawn('b', 5, 6),  new Pawn('b', 6, 6),  new Pawn('b', 7, 6)
              }), m_colour_to_play(colour_to_play) {}

void Game::playGame()
{

}

void Game::render(QPainter &paint)
{
        m_board.render(paint);

        paint.setBrush(Qt::white);
        if (m_colour_to_play == 'w') {
                paint.drawEllipse(626 - 20,
                                  626 - 40, 8, 8);
        }

        if (m_colour_to_play == 'b') {
                paint.drawEllipse(626 - 20,
                                  40, 8, 8);
        }

        if (m_circled_squares.size() != 0) {
                paint.setBrush(Qt::blue);
                for (std::pair<int, int>& cell : m_circled_squares) {
                        paint.drawEllipse(70 * cell.first + 60,
                                          590 - (70 * cell.second + 40), 15, 15);
                }
        }
}

void Game::select_square(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8) {
                return;
        }

        Piece* p = m_board[x][y];

        if (p != nullptr and p->colour() == m_colour_to_play) {
                m_circled_squares = legal_moves(x, y);
                if (m_circled_squares.size() != 0) {
                        m_x = x;
                        m_y = y;
                }

                return;
        }

        for (std::pair<int, int>& sq : m_circled_squares) {
                if (x == sq.first && y == sq.second) {
                        m_board.move_piece(m_x, m_y, x, y);
                        m_colour_to_play = (m_colour_to_play == 'w') ? 'b' : 'w';
                }
        }

        m_circled_squares.clear();
}

std::vector<std::pair<int, int>> Game::legal_moves(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8 or m_board[x][y] == nullptr or m_board[x][y]->colour() != m_colour_to_play) {
                return {};
        }

        std::vector<std::pair<int, int>> moves = m_board[x][y]->legal_moves(m_board);

        std::vector<std::pair<int, int>> possible_moves;

        for (std::pair<int, int> coord : moves) {
                Board tmp = m_board;
                tmp.move_piece(x, y, coord.first, coord.second);
                if (tmp.check() != m_colour_to_play) {
                        possible_moves.push_back({coord.first, coord.second});
                }
        }

        return possible_moves;
}
