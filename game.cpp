#include "game.h"
#include <iostream>

Game::Game(): m_board(
                  {
                          std::make_shared<Pawn>('w', 0, 1), std::make_shared<Pawn>('w', 1, 1), std::make_shared<Pawn>('w', 2, 1), std::make_shared<Pawn>('w', 3, 1),
                          std::make_shared<Pawn>('w', 4, 1), std::make_shared<Pawn>('w', 5, 1), std::make_shared<Pawn>('w', 6, 1), std::make_shared<Pawn>('w', 7, 1),
                          std::make_shared<Rook>('w', 0, 0), std::make_shared<Knight>('w', 1, 0),std::make_shared<Bishop>('w', 2, 0), std::make_shared<Queen>('w', 3, 0),
                          std::make_shared<King>('w', 4, 0), std::make_shared<Bishop>('w', 5, 0), std::make_shared<Knight>('w', 6, 0), std::make_shared<Rook>('w', 7, 0)
                  },

                  {
                          std::make_shared<Pawn>('b', 0, 6), std::make_shared<Pawn>('b', 1, 6), std::make_shared<Pawn>('b', 2, 6), std::make_shared<Pawn>('b', 3, 6),
                          std::make_shared<Pawn>('b', 4, 6), std::make_shared<Pawn>('b', 5, 6), std::make_shared<Pawn>('b', 6, 6), std::make_shared<Pawn>('b', 7, 6),
                          std::make_shared<Rook>('b', 0, 7), std::make_shared<Knight>('b', 1, 7), std::make_shared<Bishop>('b', 2, 7), std::make_shared<Queen>('b', 3, 7),
                          std::make_shared<King>('b', 4, 7), std::make_shared<Bishop>('b', 5, 7), std::make_shared<Knight>('b', 6, 7), std::make_shared<Rook>('b', 7, 7),
                  }
              ) {}

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

        auto p = m_board[x][y];

        if (p != nullptr and p->colour() == m_colour_to_play) {
                m_circled_squares = m_board.legal_moves(x, y);
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

// ***********************************************************
//        if (m_colour_to_play == 'b') {
//                next_move();
//                m_colour_to_play = 'w';
//        }
// ***********************************************************
}

std::vector<std::shared_ptr<Board>> Game::actions(Board& board, char player)
{
        std::vector<std::shared_ptr<Board>> actions;

        if (player == 'w') {
                for (auto& p : board.get_white_pieces()) {

                        std::vector<std::pair<int, int>> moves = board.legal_moves(p->x(), p->y());

                        for (std::pair<int, int> m : moves) {
                                std::shared_ptr<Board> new_board = std::make_shared<Board>(board);
                                new_board->move_piece(p->x(), p->y(), m.first, m.second);
                                actions.push_back(new_board);
                        }
                }
        }

        if (player == 'b') {
                for (auto& p : board.get_black_pieces()) {
                        std::vector<std::pair<int, int>> moves = board.legal_moves(p->x(), p->y());

                        for (std::pair<int, int> m : moves) {
                                std::shared_ptr<Board> new_board = std::make_shared<Board>(board);
                                new_board->move_piece(p->x(), p->y(), m.first, m.second);
                                actions.push_back(new_board);

                        }
                }
        }

        return actions;
}

void Game::next_move()
{
        int depth = 2;

        int value = 0;

        if (m_colour_to_play == 'w') {
                value = INT_MIN;
                for (auto& b : actions(m_board, m_colour_to_play)) {
                        if (minimax(b, depth, INT_MIN, INT_MAX, 'b') > value) {
                                m_board = Board(*b);
                        }
                }
        }

        if (m_colour_to_play == 'b') {
                value = INT_MAX;
                for (auto& b : actions(m_board, m_colour_to_play)) {
                        if (minimax(b, depth, INT_MIN, INT_MAX, 'w') < value) {
                                m_board = Board(*b);
                        }
                }
        }

//        std::cout << "VALUE = " << value << std::endl;
}

int Game::minimax(std::shared_ptr<Board> node, int depth, int alpha, int beta, char player)
{

        if (depth <= 0 or node->checkmate(player)) {
                return node->evaluate();
        }

//        node->print_board();

        int value = 0;

        if (player == 'w') {

                auto moves = actions(*node, 'w');

                value = INT_MIN;
                for (auto &b : moves) {
                        value = std::max(value, minimax(b, depth - 1, alpha, beta, 'b'));
                        alpha = std::max(alpha, value);
                        if (alpha >= beta) {
                                break;
                        }
                }
        }

        if (player == 'b') {

                auto moves = actions(*node, 'b');

                value = INT_MAX;
                for (auto &b : moves) {
                        value = std::min(value, minimax(b, depth - 1, alpha, beta, 'w'));
                        beta = std::min(alpha, value);
                        if (beta <= alpha) {
                                break;
                        }
                }
        }

        return value;
}
