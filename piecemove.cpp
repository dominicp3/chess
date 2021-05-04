#include "piecemove.h"

using namespace std;

void PieceMove::castling(GameState& board, vector<unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny)
{
        unique_ptr<GameState> new_board = make_unique<GameState>(board);

        if ((*new_board)(ox, oy) == 'k') {
                // WHITE CASTLE SHORT
                if (not new_board->white_king_moved and nx == 6) {
                        new_board->move_piece(ox, oy, nx-1, ny);
                        new_board->white_to_move = false;

                        if (is_white_in_check(*new_board)) {
                                return;
                        }

                        ox = nx-1;

                }

                // WHITE CASTLE LONG
                if (not new_board->white_king_moved and nx == 2) {
                        new_board->move_piece(ox, oy, nx+1, ny);
                        new_board->white_to_move = false;

                        if (is_white_in_check(*new_board)) {
                                return;
                        }

                        ox = nx+1;
                }
        } else

        if ((*new_board)(ox, oy) == 'K') {

                // BLACK CASTLE SHORT
                if (not new_board->black_king_moved and nx == 6) {
                        new_board->move_piece(ox, oy, nx-1, ny);
                        new_board->white_to_move = true;

                        if (is_black_in_check(*new_board)) {
                                return;
                        }

                        ox = nx-1;
                }

                // BLACK CASTLE LONG
                if (not new_board->black_king_moved and nx == 2) {
                        new_board->move_piece(ox, oy, nx+1, ny);
                        new_board->white_to_move = true;

                        if (is_black_in_check(*new_board)) {
                                return;
                        }

                        ox = nx+1;
                }
        }

        new_board->move_piece(ox, oy, nx, ny);

        // WHITE CASTLE SHORT MOVE ROOK
        if (nx == 6 and ny == 0) {
                new_board->move_piece(7, 0, 5, 0);
                new_board->current_move = {6, 0};
                new_board->white_to_move = false;

                if (not is_white_in_check(*new_board)) {
                        moves.push_back(move(new_board));
                }
        }

        // WHITE CASTLE LONG MOVE ROOK
        if (nx == 2 and ny == 0) {
                new_board->move_piece(0, 0, 3, 0);
                new_board->current_move = {2, 0};
                new_board->white_to_move = false;

                if (not is_white_in_check(*new_board)) {
                        moves.push_back(move(new_board));
                }
        }

        // BLACK CASTLE SHORT MOVE ROOK
        if (nx == 6 and ny == 7) {
                new_board->move_piece(7, 7, 5, 7);
                new_board->current_move = {6, 7};
                new_board->white_to_move = true;

                if (not is_black_in_check(*new_board)) {
                        moves.push_back(move(new_board));
                }
        }

        // BLACK CASTLE LONG MOVE ROOK
        if (nx == 2 and ny == 7) {
                new_board->move_piece(0, 7, 3, 7);
                new_board->current_move = {2, 7};
                new_board->white_to_move = true;

                if (not is_black_in_check(*new_board)) {
                        moves.push_back(move(new_board));
                }
        }
}

vector<unique_ptr<GameState>> PieceMove::moves(GameState& board, int x, int y)
{
        char piece = board(x, y);

        if (piece == 'p') {
                return pawn_w_legal(board, x, y);
        }

        if (piece == 'P') {
                return pawn_b_legal(board, x, y);
        }

        if (piece == 'r' or piece == 'R') {
                return rook_legal(board, x, y);
        }

        if (piece == 'n' or piece == 'N') {
                return knight_legal(board, x, y);
        }

        if (piece == 'b' or piece == 'B') {
                return bishop_legal(board, x, y);
        }

        if (piece == 'q' or piece == 'Q') {
                return queen_legal(board, x, y);
        }

        if (piece == 'k' or piece == 'K') {
                return king_legal(board, x, y);
        }

        return {};
}

vector<pair<int, int>> PieceMove::squares(GameState& board, int x, int y)
{
        char piece = board(x, y);

        if (piece == 'p') {
                return pawn_w(board, x, y);
        }

        if (piece == 'P') {
                return pawn_b(board, x, y);
        }

        if (piece == 'r' or piece == 'R') {
                return rook(board, x, y);
        }

        if (piece == 'n' or piece == 'N') {
                return knight(board, x, y);
        }

        if (piece == 'b' or piece == 'B') {
                return bishop(board, x, y);
        }

        if (piece == 'q' or piece == 'Q') {
                return queen(board, x, y);
        }

        if (piece == 'k' or piece == 'K') {
                return king(board, x, y);
        }

        return {};
}

int PieceMove::is_white(char p)
{
        if (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k') {
                return 1;
        }

        if (p == 'P' or p == 'R' or p == 'N' or p == 'B' or p == 'Q' or p == 'K') {
                return 0;
        }

        return -1;
}

bool PieceMove::is_square_valid(GameState& board, int x, int y)
{
        char square = board(x, y);

        if (square == -1) {
                return false;
        }

        return (square == 0) or ((is_white(square)) != board.white_to_move);
}

void PieceMove::add_move_legal(GameState& board, vector<unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny)
{
        char piece = board(ox, oy);

//      CASTLING
        if ((piece == 'k' and not board.white_king_moved and (nx == 2 or nx == 6))
         or (piece == 'K' and not board.black_king_moved and (nx == 2 or nx == 6)))
        {
                board.en_passant = false;
                castling(board, moves, ox, oy, nx, ny);
                return;
        }

        unique_ptr<GameState> new_board = make_unique<GameState>(board);

//      EN PASSANT
        if (new_board->en_passant) {
                if (is_white(piece)) {
                        new_board->black_pieces.erase(board.current_move);
                } else {
                        new_board->white_pieces.erase(board.current_move);
                }
        }

//      PAWN PROMOTION
        if (piece == 'p' and ny == 7) {
                new_board->white_pieces[{ox, oy}] = 'q';
        }
        if (piece == 'P' and ny == 0) {
                new_board->black_pieces[{ox, oy}] = 'Q';
        }

        new_board->move_piece(ox, oy, nx, ny);
        new_board->white_to_move = not new_board->white_to_move;

        board.en_passant = false;

        if (is_white((*new_board)(nx, ny)) and not is_white_in_check(*new_board)) {
                moves.push_back(move(new_board));
        } else

        if (not is_white((*new_board)(nx, ny)) and not is_black_in_check(*new_board)) {
                moves.push_back(move(new_board));
        }
}

vector<pair<int, int>> PieceMove::pawn_w(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        if (y == 1 and !board(x, y + 1) and !board(x, y + 2)) {
                moves.push_back({x, y + 2});
        }

        if (!board(x, y + 1)) {
                moves.push_back({x, y + 1});
        }

        if (board(x + 1, y + 1) > 0 and is_square_valid(board, x + 1, y + 1)) {
                moves.push_back({x + 1, y + 1});
        }

        if (board(x - 1, y + 1) > 0 and is_square_valid(board, x - 1, y + 1)) {
                moves.push_back({x - 1, y + 1});
        }

//      EN PASSANT
        if (board(board.current_move) == 'P') {
                if (board.current_move == make_pair(x + 1, y)) {
                        moves.push_back({x + 1, y + 1});
                }

                if (board.current_move == make_pair(x - 1, y)) {
                        moves.push_back({x - 1, y + 1});
                }
        }

        return moves;
}

vector<pair<int, int>> PieceMove::pawn_b(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        if (y == 6 and !board(x, y - 1) and !board(x, y - 2)) {
                moves.push_back({x, y - 2});
        }

        if (!board(x, y - 1)) {
                moves.push_back({x, y - 1});
        }

        if (board(x + 1, y - 1) > 0 and is_square_valid(board, x + 1, y - 1)) {
                moves.push_back({x + 1, y - 1});
        }

        if (board(x - 1, y - 1) > 0 and is_square_valid(board, x - 1, y - 1)) {
                moves.push_back({x - 1, y - 1});
        }

//      EN PASSANT
        if (board(board.current_move) == 'p') {
                if (board.current_move == make_pair(x + 1, y)) {
                        moves.push_back({x + 1, y - 1});
                }

                if (board.current_move == make_pair(x - 1, y)) {
                        moves.push_back({x - 1, y - 1});
                }
        }

        return moves;
}

vector<pair<int, int>> PieceMove::rook(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        for (int right = x+1; right < 8; right++) {
                if (is_square_valid(board, right, y)) {
                        moves.push_back({right, y});
                        if (board(right, y) > 0) {
                                break;
                        }
                } else break;
        }

        for (int left = x-1; left >= 0; left--) {
                if (is_square_valid(board, left, y)) {
                        moves.push_back({left, y});
                        if (board(left, y) > 0) {
                                break;
                        }
                } else break;
        }

        for (int top = y+1; top < 8; top++) {
                if (is_square_valid(board, x, top)) {
                        moves.push_back({x, top});
                        if (board(x, top) > 0) {
                                break;
                        }
                } else break;
        }

        for (int bottom = y-1; bottom >= 0; bottom--) {
                if (is_square_valid(board, x, bottom)) {
                        moves.push_back({x, bottom});
                        if (board(x, bottom) > 0) {
                                break;
                        }
                } else break;
        }

        return moves;
}

vector<pair<int, int>> PieceMove::knight(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        if (is_square_valid(board, x+2, y+1)) {
                moves.push_back({x+2, y+1});
        }

        if (is_square_valid(board, x+2, y-1)) {
                moves.push_back({x+2, y-1});
        }

        if (is_square_valid(board, x-2, y+1)) {
                moves.push_back({x-2, y+1});
        }

        if (is_square_valid(board, x-2, y-1)) {
                moves.push_back({x-2, y-1});
        }

        if (is_square_valid(board, x+1, y+2)) {
                moves.push_back({x+1, y+2});
        }

        if (is_square_valid(board, x-1, y+2)) {
                moves.push_back({x-1, y+2});
        }

        if (is_square_valid(board, x+1, y-2)) {
                moves.push_back({x+1, y-2});
        }

        if (is_square_valid(board, x-1, y-2)) {
                moves.push_back({x-1, y-2});
        }

        return moves;
}

vector<pair<int, int>> PieceMove::bishop(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        for (int ru = 1; x + ru < 8 and y + ru < 8; ru++) {

                if (is_square_valid(board, x + ru, y + ru)) {
                        moves.push_back({x + ru, y + ru});
                        if (board(x + ru, y + ru) > 0) {
                                break;
                        }
                } else break;
        }

        for (int rd = 1; x + rd < 8 and y - rd >= 0; rd++) {
                if (is_square_valid(board, x + rd, y - rd)) {
                        moves.push_back({x + rd, y - rd});
                        if (board(x + rd, y - rd) > 0) {
                                break;
                        }
                } else break;
        }

        for (int lu = 1; x - lu >= 0 and y + lu < 8; lu++) {
                if (is_square_valid(board, x - lu, y + lu)) {
                        moves.push_back({x - lu, y + lu});
                        if (board(x - lu, y + lu) > 0) {
                                break;
                        }
                } else break;
        }

        for (int ld = 1; x - ld >= 0 and y - ld >= 0; ld++) {
                if (is_square_valid(board, x - ld, y - ld)) {
                        moves.push_back({x - ld, y - ld});
                        if (board(x - ld, y - ld) > 0) {
                                break;
                        }
                } else break;
        }

        return moves;
}

vector<pair<int, int>> PieceMove::queen(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        auto rook_moves = rook(board, x, y);
        auto bishop_moves = bishop(board, x, y);

        for (auto& m : rook_moves) {
                moves.push_back(m);
        }

        for (auto& m : bishop_moves) {
                moves.push_back(m);
        }

        return moves;
}

vector<pair<int, int>> PieceMove::king(GameState& board, int x, int y)
{
        vector<pair<int, int>> moves;

        if (is_square_valid(board, x + 1, y)) {
                moves.push_back({x + 1, y});
        }

        if (is_square_valid(board, x - 1, y)) {
                moves.push_back({x - 1, y});
        }

        if (is_square_valid(board, x, y + 1)) {
                moves.push_back({x, y + 1});
        }

        if (is_square_valid(board, x, y - 1)) {
                moves.push_back({x, y - 1});
        }

        if (is_square_valid(board, x + 1, y + 1)) {
                moves.push_back({x + 1, y + 1});
        }

        if (is_square_valid(board, x - 1, y - 1)) {
                moves.push_back({x - 1, y - 1});
        }

        if (is_square_valid(board, x - 1, y + 1)) {
                moves.push_back({x - 1, y + 1});
        }

        if (is_square_valid(board, x + 1, y - 1)) {
                moves.push_back({x + 1, y - 1});
        }

        // CASTLING SHORT WHITE
        if (is_white(board(x, y)) and not board.white_king_moved and not board.white_hrook_moved) {
                moves.push_back({x + 2, y});
        }

        // CASTLING LONG WHITE
        if (is_white(board(x, y)) and not board.white_king_moved and not board.white_arook_moved) {
                moves.push_back({x - 2, y});
        }

        // CASTLING SHORT BLACK
        if (not is_white(board(x, y)) and not board.black_king_moved and not board.black_hrook_moved) {
                moves.push_back({x + 2, y});
        }

        // CASTLING LONG BLACK
        if (not is_white(board(x, y)) and not board.black_king_moved and not board.black_arook_moved) {
                moves.push_back({x - 2, y});
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::pawn_w_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        if (y == 1 and !board(x, y + 1) and !board(x, y + 2)) {
                add_move_legal(board, moves, x, y, x, y + 2);
        }

        if (!board(x, y + 1)) {
                add_move_legal(board, moves, x, y, x, y + 1);
        }

        if (board(x + 1, y + 1) > 0 and is_square_valid(board, x + 1, y + 1)) {
                add_move_legal(board, moves, x, y, x + 1, y + 1);
        }

        if (board(x - 1, y + 1) > 0 and is_square_valid(board, x - 1, y + 1)) {
                add_move_legal(board, moves, x, y, x - 1, y + 1);
        }

//      EN PASSANT
        if (board(board.current_move) == 'P') {
                if (board.current_move == make_pair(x + 1, y)) {
                        board.en_passant = true;
                        add_move_legal(board, moves, x, y, x+1, y+1);
                }

                if (board.current_move == make_pair(x - 1, y)) {
                        board.en_passant = true;
                        add_move_legal(board, moves, x, y, x-1, y+1);
                }
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::pawn_b_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        if (y == 6 and !board(x, y - 1) and !board(x, y - 2)) {
                add_move_legal(board, moves, x, y, x, y - 2);
        }

        if (!board(x, y - 1)) {
                add_move_legal(board, moves, x, y, x, y - 1);
        }

        if (board(x + 1, y - 1) > 0 and is_square_valid(board, x + 1, y - 1)) {
                add_move_legal(board, moves, x, y, x + 1, y - 1);
        }

        if (board(x - 1, y - 1) > 0 and is_square_valid(board, x - 1, y - 1)) {
                add_move_legal(board, moves, x, y, x - 1, y - 1);
        }

        //      EN PASSANT
                if (board(board.current_move) == 'p') {
                        if (board.current_move == make_pair(x + 1, y)) {
                                board.en_passant = true;
                                add_move_legal(board, moves, x, y, x+1, y-1);
                        }

                        if (board.current_move == make_pair(x - 1, y)) {
                                board.en_passant = true;
                                add_move_legal(board, moves, x, y, x-1, y-1);
                        }
                }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::rook_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        for (int right = x+1; right < 8; right++) {
                if (is_square_valid(board, right, y)) {
                        add_move_legal(board, moves, x, y, right, y);
                        if (board(right, y) > 0) {
                                break;
                        }
                } else break;
        }

        for (int left = x-1; left >= 0; left--) {
                if (is_square_valid(board, left, y)) {
                        add_move_legal(board, moves, x, y, left, y);
                        if (board(left, y) > 0) {
                                break;
                        }
                } else break;
        }

        for (int top = y+1; top < 8; top++) {
                if (is_square_valid(board, x, top)) {
                        add_move_legal(board, moves, x, y, x, top);
                        if (board(x, top) > 0) {
                                break;
                        }
                } else break;
        }

        for (int bottom = y-1; bottom >= 0; bottom--) {
                if (is_square_valid(board, x, bottom)) {
                        add_move_legal(board, moves, x, y, x, bottom);
                        if (board(x, bottom) > 0) {
                                break;
                        }
                } else break;
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::knight_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        if (is_square_valid(board, x+2, y+1)) {
                add_move_legal(board, moves, x, y, x+2, y+1);
        }

        if (is_square_valid(board, x+2, y-1)) {
                add_move_legal(board, moves, x, y, x+2, y-1);
        }

        if (is_square_valid(board, x-2, y+1)) {
                add_move_legal(board, moves, x, y, x-2, y+1);
        }

        if (is_square_valid(board, x-2, y-1)) {
                add_move_legal(board, moves, x, y, x-2, y-1);
        }

        if (is_square_valid(board, x+1, y+2)) {
                add_move_legal(board, moves, x, y, x+1, y+2);
        }

        if (is_square_valid(board, x-1, y+2)) {
                add_move_legal(board, moves, x, y, x-1, y+2);
        }

        if (is_square_valid(board, x+1, y-2)) {
                add_move_legal(board, moves, x, y, x+1, y-2);
        }

        if (is_square_valid(board, x-1, y-2)) {
                add_move_legal(board, moves, x, y, x-1, y-2);
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::bishop_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        for (int ru = 1; x + ru < 8 and y + ru < 8; ru++) {
                if (is_square_valid(board, x + ru, y + ru)) {
                        add_move_legal(board, moves, x, y, x + ru, y + ru);
                        if (board(x + ru, y + ru) > 0) {
                                break;
                        }
                } else break;
        }

        for (int rd = 1; x + rd < 8 and y - rd >= 0; rd++) {
                if (is_square_valid(board, x + rd, y - rd)) {
                        add_move_legal(board, moves, x, y, x + rd, y - rd);
                        if (board(x + rd, y - rd) > 0) {
                                break;
                        }
                } else break;
        }

        for (int lu = 1; x - lu >= 0 and y + lu < 8; lu++) {
                if (is_square_valid(board, x - lu, y + lu)) {
                        add_move_legal(board, moves, x, y, x - lu, y + lu);
                        if (board(x - lu, y + lu) > 0) {
                                break;
                        }
                } else break;
        }

        for (int ld = 1; x - ld >= 0 and y - ld >= 0; ld++) {
                if (is_square_valid(board, x - ld, y - ld)) {
                        add_move_legal(board, moves, x, y, x - ld, y - ld);
                        if (board(x - ld, y - ld) > 0) {
                                break;
                        }
                } else break;
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::queen_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        auto rook_moves = rook_legal(board, x, y);
        auto bishop_moves = bishop_legal(board, x, y);

        for (auto& m : rook_moves) {
                moves.push_back(make_unique<GameState>(*m));
        }

        for (auto& m : bishop_moves) {
                moves.push_back(make_unique<GameState>(*m));
        }

        return moves;
}

vector<unique_ptr<GameState>> PieceMove::king_legal(GameState& board, int x, int y)
{
        vector<unique_ptr<GameState>> moves;

        if (is_square_valid(board, x + 1, y)) {
                add_move_legal(board, moves, x, y, x + 1, y);
        }

        if (is_square_valid(board, x - 1, y)) {
                add_move_legal(board, moves, x, y, x - 1, y);
        }

        if (is_square_valid(board, x, y + 1)) {
                add_move_legal(board, moves, x, y, x, y + 1);
        }

        if (is_square_valid(board, x, y - 1)) {
                add_move_legal(board, moves, x, y, x, y - 1);
        }

        if (is_square_valid(board, x + 1, y + 1)) {
                add_move_legal(board, moves, x, y, x + 1, y + 1);
        }

        if (is_square_valid(board, x - 1, y - 1)) {
                add_move_legal(board, moves, x, y, x - 1, y - 1);
        }

        if (is_square_valid(board, x - 1, y + 1)) {
                add_move_legal(board, moves, x, y, x - 1, y + 1);
        }

        if (is_square_valid(board, x + 1, y - 1)) {
                add_move_legal(board, moves, x, y, x + 1, y - 1);
        }

        // CASTLING SHORT WHITE
        if (is_white(board(x, y)) and not board.white_king_moved and not board.white_hrook_moved) {
                if (!board(x+1, y) and !board(x+2, y)) {
                        add_move_legal(board, moves, x, y, x+2, y);
                }
        }

        // CASTLING LONG WHITE
        if (is_white(board(x, y)) and not board.white_king_moved and not board.white_arook_moved) {
                if (!board(x-1, y) and !board(x-2, y)) {
                        add_move_legal(board, moves, x, y, x-2, y);
                }
        }

        // CASTLING SHORT BLACK
        if (not is_white(board(x, y)) and not board.black_king_moved and not board.black_hrook_moved) {
                if (!board(x+1, y) and !board(x+2, y)) {
                        add_move_legal(board, moves, x, y, x+2, y);
                }
        }

        // CASTLING LONG BLACK
        if (not is_white(board(x, y)) and not board.black_king_moved and not board.black_arook_moved) {
                if (!board(x-1, y) and !board(x-2, y)) {
                        add_move_legal(board, moves, x, y, x-2, y);
                }
        }

        return moves;
}

bool PieceMove::is_white_in_check(GameState& board)
{
        piece_map& black_pieces = board.black_pieces;

        for (auto it = black_pieces.begin(); it != black_pieces.end(); it++) {
                for (auto& m : squares(board, it->first.first, it->first.second)) {
                        if (m == board.white_king_coord) {
                                return true;
                        }
                }
        }

        return false;
}

bool PieceMove::is_black_in_check(GameState& board)
{
        piece_map& white_pieces = board.white_pieces;

        for (auto it = white_pieces.begin(); it != white_pieces.end(); it++) {
                for (auto& m : squares(board, it->first.first, it->first.second)) {
                        if (m == board.black_king_coord) {
                                return true;
                        }
                }
        }

        return false;
}
