#include "game.h"

using namespace std;

void Game::render(QPainter &paint)
{
        render_board(paint);
        render_player_indicator(paint);
        render_pieces(paint);
        render_move_circles(paint);
}

void Game::render_pieces(QPainter &paint)
{
        for (unsigned int x = 0; x < 8; x++) {
                for (unsigned int y = 0; y < 8; y++) {
                        char piece = m_gamestate(x, y);
                        if (piece > 0) {
                                switch (piece) {
                                case 'p': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_pawn_icon);
                                          break;
                                case 'n': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_knight_icon);
                                          break;
                                case 'b': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_bishop_icon);
                                          break;
                                case 'r': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_rook_icon);
                                          break;
                                case 'q': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_queen_icon);
                                          break;
                                case 'k': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_white_king_icon);
                                          break;

                                case 'P': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_pawn_icon);
                                          break;
                                case 'N': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_knight_icon);
                                          break;
                                case 'B': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_bishop_icon);
                                          break;
                                case 'R': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_rook_icon);
                                          break;
                                case 'Q': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_queen_icon);
                                          break;
                                case 'K': paint.drawPixmap(70 * x + 37, 626 - (69 * y + 103), m_black_king_icon);
                                          break;
                                default: break;
                                }
                        }
                }
        }
}

void Game::render_board(QPainter &paint)
{
        QPixmap boardImage {QDir::currentPath().append("/images/board.jpg")};
        paint.drawPixmap(0, 0, boardImage);
}

void Game::render_player_indicator(QPainter& paint)
{
        paint.setBrush(Qt::white);

        if (m_gamestate.white_to_move) {
                paint.drawEllipse(626 - 20,
                                  626 - 40, 8, 8);
        } else {
                paint.drawEllipse(626 - 20,
                                  40, 8, 8);
        }
}

void Game::render_move_circles(QPainter& paint)
{
        if (m_potential_states.size() != 0) {
                paint.setBrush(Qt::blue);
                for (auto& state : m_potential_states) {
                        pair<int, int> cell = state->current_move;
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

        char p = m_gamestate(x, y);

        if (p > 0 and is_white(p) == m_gamestate.white_to_move) {

                m_potential_states = m_piecemove.moves(m_gamestate, x, y);
                if (m_potential_states.size() != 0) {
                        m_x = x;
                        m_y = y;
                }

                return;
        }

        for (auto& state : m_potential_states) {

                if (make_pair(x, y) == state->current_move) {
                        m_gamestate = GameState(*state);
                }
        }

        m_potential_states.clear();
}

bool Game::is_white(char p)
{
        if (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k') {
                return true;
        }

        return false;
}
