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

//      CASTLING CONDITIONS
        if (m_colour == 'w') {
                if (!m_aux) {
                        if (board[0][0] != nullptr and board[0][0]->type() == 'r' and !board[0][0]->get_aux()) {
                                if (board[1][0] == nullptr and board[2][0] == nullptr and board[3][0] == nullptr) {
                                        Board knight_sq = board;
                                        Board bishop_sq = board;
                                        Board queen_sq = board;

                                        knight_sq.move_piece(4, 0, 1, 0);
                                        bishop_sq.move_piece(4, 0, 1, 0);
                                        queen_sq.move_piece(4, 0, 1, 0);

                                        if (knight_sq.check() == 0 and bishop_sq.check() == 0 and queen_sq.check() == 0) {
                                                moves.push_back({2, 0});
                                        }
                                }
                        }


                        if (board[7][0] != nullptr and board[7][0]->type() == 'r' and !board[7][0]->get_aux()) {
                                if (board[5][0] == nullptr and board[6][0] == nullptr) {
                                        Board bishop_sq = board;
                                        Board knight_sq = board;

                                        bishop_sq.move_piece(4, 0, 5, 0);
                                        knight_sq.move_piece(4, 0, 6, 0);


                                        if (knight_sq.check() == 0 and bishop_sq.check() == 0) {
                                                moves.push_back({6, 0});
                                        }
                                }
                        }
                }
        }

        if (m_colour == 'b') {
                if (!m_aux) {
                        if (board[0][7] != nullptr and board[0][7]->type() == 'r' and !board[0][7]->get_aux()) {
                                if (board[1][7] == nullptr and board[2][7] == nullptr and board[3][7] == nullptr) {
                                        Board knight_sq = board;
                                        Board bishop_sq = board;
                                        Board queen_sq = board;

                                        knight_sq.move_piece(4, 7, 1, 7);
                                        bishop_sq.move_piece(4, 7, 1, 7);
                                        queen_sq.move_piece(4, 7, 1, 7);

                                        if (knight_sq.check() == 0 and bishop_sq.check() == 0 and queen_sq.check() == 0) {
                                                moves.push_back({2, 7});
                                        }
                                }
                        }


                        if (board[7][7] != nullptr and board[7][7]->type() == 'r' and !board[7][7]->get_aux()) {
                                if (board[5][7] == nullptr and board[6][7] == nullptr) {
                                        Board bishop_sq = board;
                                        Board knight_sq = board;

                                        bishop_sq.move_piece(4, 7, 5, 7);
                                        knight_sq.move_piece(4, 7, 6, 7);


                                        if (knight_sq.check() == 0 and bishop_sq.check() == 0) {
                                                moves.push_back({6, 7});
                                        }
                                }
                        }
                }
        }

        return moves;
}
