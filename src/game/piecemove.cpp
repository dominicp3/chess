#include "game/piecemove.h"

using namespace std;

namespace piecemove {

        namespace {
                int is_white(char p)
                {
                        if (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k') {
                                return 1;
                        }

                        if (p == 'P' or p == 'R' or p == 'N' or p == 'B' or p == 'Q' or p == 'K') {
                                return 0;
                        }

                        return -1;
                }

                bool is_square_valid(GameState& board, int x, int y)
                {
                        char square = board(x, y);

                        if (square == -1) {
                                return false;
                        }

                        return (square == 0) or ((is_white(square)) != board.white_to_move);
                }

                void en_passant(unique_ptr<GameState>& board)
                {
                        if (board->en_passant and board->en_passant_white) {
                                board->black_pieces.erase(board->current_move);
                        } else if (board->en_passant and board->en_passant_black) {
                                board->white_pieces.erase(board->current_move);
                        }

                        if (board->white_to_move) {
                                board->en_passant_white = false;
                        } else {
                                board->en_passant_black = false;
                        }
                        board->en_passant = false;
                }

                bool pawn_check(GameState& board, int x, int y)
                {
                        int king_x = board.white_to_move ? board.black_king_coord.first : board.white_king_coord.first;
                        int king_y = board.white_to_move ? board.black_king_coord.second : board.white_king_coord.second;

                        if (board.white_to_move) {
                                if (x + 1 == king_x and y + 1 == king_y) {
                                        return true;
                                }

                                if (x - 1 == king_x and y + 1 == king_y) {
                                        return true;
                                }
                        } else {
                                if (x + 1 == king_x and y - 1 == king_y) {
                                        return true;
                                }

                                if (x - 1 == king_x and y - 1 == king_y) {
                                        return true;
                                }
                        }

                        return false;
                }

                bool rook_check(GameState& board, int x, int y)
                {
                        int king_x = board.white_to_move ? board.black_king_coord.first : board.white_king_coord.first;
                        int king_y = board.white_to_move ? board.black_king_coord.second : board.white_king_coord.second;



                        if (y == king_y and x < king_x) {
                                for (int right = x+1; right < 8; right++) {
                                        if (right == king_x) {
                                                return true;
                                        }
                                        if (board(right, y) > 0) {
                                                return false;
                                        }
                                }
                        }

                        if (y == king_y and x > king_x) {
                                for (int left = x-1; left >= 0; left--) {
                                        if (left == king_x) {
                                                return true;
                                        }
                                        if (board(left, y) > 0) {
                                                return false;
                                        }
                                }
                        }

                        if (x == king_x and y < king_y) {
                                for (int top = y+1; top < 8; top++) {
                                        if (top == king_y) {
                                                return true;
                                        }
                                        if (board(x, top) > 0) {
                                                return false;
                                        }
                                }
                        }

                        if (x == king_x and y > king_y) {
                                for (int bottom = y-1; bottom >= 0; bottom--) {
                                        if (bottom == king_y) {
                                                return true;
                                        }
                                        if (board(x, bottom) > 0) {
                                                return false;
                                        }
                                }
                        }

                        return false;
                }

                bool knight_check(GameState& board, int x, int y)
                {
                        int king_x = board.white_to_move ? board.black_king_coord.first : board.white_king_coord.first;
                        int king_y = board.white_to_move ? board.black_king_coord.second : board.white_king_coord.second;

                        if (x+2 == king_x and y+1 == king_y) {
                                return true;
                        }

                        if (x+2 == king_x and y-1 == king_y) {
                                return true;
                        }

                        if (x-2 == king_x and y+1 == king_y) {
                                return true;
                        }

                        if (x-2 == king_x and y-1 == king_y) {
                                return true;
                        }

                        if (x+1 == king_x and y+2 == king_y) {
                                return true;
                        }

                        if (x-1 == king_x and y+2 == king_y) {
                                return true;
                        }

                        if (x+1 == king_x and y-2 == king_y) {
                                return true;
                        }

                        if (x-1 == king_x and y-2 == king_y) {
                                return true;
                        }

                        return false;
                }

                bool bishop_check(GameState& board, int x, int y)
                {
                        int king_x = board.white_to_move ? board.black_king_coord.first : board.white_king_coord.first;
                        int king_y = board.white_to_move ? board.black_king_coord.second : board.white_king_coord.second;

                //      RIGHT UP
                        if (x - king_x == y - king_y and x - king_x < 0) {
                                for (int ru = 1; x + ru < 8 and y + ru < 8; ru++) {
                                        if (x + ru == king_x) {
                                                return true;
                                        }
                                        if (board(x + ru, y + ru) > 0) {
                                                return false;
                                        }
                                }
                        }

                //      RIGHT DOWN
                        if (x - king_x == -(y - king_y) and x - king_x < 0) {
                                for (int rd = 1; x + rd < 8 and y - rd >= 0; rd++) {
                                        if (x + rd == king_x) {
                                                return true;
                                        }
                                        if (board(x + rd, y - rd) > 0) {
                                                return false;
                                        }
                                }
                        }

                //      LEFT UP
                        if (x - king_x == -(y - king_y) and x - king_x > 0) {
                                for (int lu = 1; x - lu >= 0 and y + lu < 8; lu++) {
                                        if (x - lu == king_x) {
                                                return true;
                                        }
                                        if (board(x - lu, y + lu) > 0) {
                                                return false;
                                        }
                                }
                        }

                //      LEFT DOWN
                        if (x - king_x == y - king_y and x - king_x > 0) {
                                for (int ld = 1; x - ld >= 0 and y - ld >= 0; ld++) {
                                        if (x - ld== king_x) {
                                                return true;
                                        }
                                        if (board(x - ld, y - ld) > 0) {
                                                return false;
                                        }
                                }
                        }

                        return false;
                }

                bool queen_check(GameState& board, int x, int y)
                {
                        return rook_check(board, x, y) or bishop_check(board, x, y);
                }

                bool king_check(GameState& board, int x, int y)
                {
                        int king_x = board.white_to_move ? board.black_king_coord.first : board.white_king_coord.first;
                        int king_y = board.white_to_move ? board.black_king_coord.second : board.white_king_coord.second;

                        if (king_x == x + 1 and king_y == y) {
                                return true;
                        }

                        if (king_x == x - 1 and king_y == y) {
                                return true;
                        }

                        if (king_x == x and king_y == y + 1) {
                                return true;
                        }

                        if (king_x == x and king_y == y - 1) {
                                return true;
                        }

                        if (king_x == x + 1 and king_y == y + 1) {
                                return true;
                        }

                        if (king_x == x - 1 and king_y == y - 1) {
                                return true;
                        }

                        if (king_x == x - 1 and king_y == y + 1) {
                                return true;
                        }

                        if (king_x == x + 1 and king_y == y - 1) {
                                return true;
                        }

                        return false;
                }

                bool piece_check(GameState& board, int x, int y)
                {
                        char piece = board(x, y);

                        if (piece == 'p' or piece == 'P') {
                                return pawn_check(board, x, y);
                        }

                        if (piece == 'r' or piece == 'R') {
                                return rook_check(board, x, y);
                        }

                        if (piece == 'n' or piece == 'N') {
                                return knight_check(board, x, y);
                        }

                        if (piece == 'b' or piece == 'B') {
                                return bishop_check(board, x, y);
                        }

                        if (piece == 'q' or piece == 'Q') {
                                return queen_check(board, x, y);
                        }

                        if (piece == 'k' or piece == 'K') {
                                return king_check(board, x, y);
                        }

                        return false;
                }

                bool in_check(GameState& board)
                {
                        piece_map& pieces = board.white_to_move ? board.white_pieces : board.black_pieces;

                        for (auto it = pieces.begin(); it != pieces.end(); it++) {
                                if (piece_check(board, it->first.first, it->first.second)) {
                                        return true;
                                }
                        }

                        return false;
                }

                bool castling(unique_ptr<GameState> board, vector<unique_ptr<GameState>>& moves, bool white, bool castle_short)
                {

                        int y = white ? 0 : 7;
                        int k = castle_short ? 1 : -1;
                        int ra = castle_short ? 7 : 0;
                        int rb = castle_short ? 5 : 3;

                        board->white_to_move = not board->white_to_move;

                        if (in_check(*board)) {
                                return false;
                        }
                        board->move_piece(4, y, 4+k, y);
                        if (in_check(*board)) {
                                return false;
                        }
                        board->move_piece(4+k, y, 4+2*k, y);

                        board->move_piece(ra, y, rb, y);
                        board->current_move = {4 + 2*k, y};

                        if (in_check(*board)) {
                                return false;
                        }

                        moves.push_back(move(board));
                        return true;
                }

                bool add_move(GameState& board, vector<unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny)
                {
                        char piece = board(ox, oy);
                        unique_ptr<GameState> new_board = make_unique<GameState>(board);

                //      EN PASSANT
                        en_passant(new_board);
//                        board.en_passant = false;

                //      CASTLING
                        if ((piece == 'k' and ox == 4 and (nx == 2 or nx == 6))
                         or (piece == 'K' and ox == 4 and (nx == 2 or nx == 6)))
                        {
                                return castling(move(new_board), moves, piece == 'k', nx == 6);
                        }

                //      PAWN PROMOTION
                        if (piece == 'p' and ny == 7) {
                                new_board->white_pieces[{ox, oy}] = 'q';
                        } else if (piece == 'P' and ny == 0) {
                                new_board->black_pieces[{ox, oy}] = 'Q';
                        }

                        new_board->move_piece(ox, oy, nx, ny);

                        if (piece_check(board, nx, ny)) {
                                new_board->in_check = true;
                        } else {
                                new_board->in_check = false;
                        }

                        new_board->white_to_move = not new_board->white_to_move;

                        if (in_check(*new_board)) {
                                return false;
                        }

                        moves.push_back(move(new_board));
                        return true;
                }

                vector<unique_ptr<GameState>> pawn_w(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        if (y == 1 and !board(x, y + 1) and !board(x, y + 2)) {
                                board.en_passant_black = true;
                                add_move(board, moves, x, y, x, y + 2);
                        }

                        board.en_passant_black = false;

                        if (!board(x, y + 1)) {
                                add_move(board, moves, x, y, x, y + 1);
                        }

                        if (board(x + 1, y + 1) > 0 and is_square_valid(board, x + 1, y + 1)) {
                                add_move(board, moves, x, y, x + 1, y + 1);
                        }

                        if (board(x - 1, y + 1) > 0 and is_square_valid(board, x - 1, y + 1)) {
                                add_move(board, moves, x, y, x - 1, y + 1);
                        }

                        if (board.en_passant_white and board.current_move == make_pair(x+1, y)) {
                                board.en_passant = true;
                                add_move(board, moves, x, y, x+1, y+1);
                        }

                        if (board.en_passant_white and board.current_move == make_pair(x-1, y)) {
                                board.en_passant = true;
                                add_move(board, moves, x, y, x-1, y+1);
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> pawn_b(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        if (y == 6 and !board(x, y - 1) and !board(x, y - 2)) {
                                board.en_passant_white = true;
                                add_move(board, moves, x, y, x, y - 2);
                        }

                        board.en_passant_white = false;

                        if (!board(x, y - 1)) {
                                add_move(board, moves, x, y, x, y - 1);
                        }

                        if (board(x + 1, y - 1) > 0 and is_square_valid(board, x + 1, y - 1)) {
                                add_move(board, moves, x, y, x + 1, y - 1);
                        }

                        if (board(x - 1, y - 1) > 0 and is_square_valid(board, x - 1, y - 1)) {
                                add_move(board, moves, x, y, x - 1, y - 1);
                        }

                        if (board.en_passant_black and board.current_move == make_pair(x+1, y)) {
                                board.en_passant = true;
                                add_move(board, moves, x, y, x+1, y-1);
                        }

                        if (board.en_passant_black and board.current_move == make_pair(x-1, y)) {
                                board.en_passant = true;
                                add_move(board, moves, x, y, x-1, y-1);
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> rook(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        for (int right = x+1; right < 8; right++) {
                                if (is_square_valid(board, right, y)) {
                                        if (not add_move(board, moves, x, y, right, y) and not board.in_check) {
                                                break;
                                        }
                                        if (board(right, y) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int left = x-1; left >= 0; left--) {
                                if (is_square_valid(board, left, y)) {
                                        if (not add_move(board, moves, x, y, left, y) and not board.in_check) {
                                                break;
                                        }
                                        if (board(left, y) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int top = y+1; top < 8; top++) {
                                if (is_square_valid(board, x, top)) {
                                        if (not add_move(board, moves, x, y, x, top) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x, top) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int bottom = y-1; bottom >= 0; bottom--) {
                                if (is_square_valid(board, x, bottom)) {
                                        if (not add_move(board, moves, x, y, x, bottom) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x, bottom) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> knight(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;
                        bool b = true;

                        if (b and is_square_valid(board, x+2, y+1)) {
                                if (not add_move(board, moves, x, y, x+2, y+1) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x+2, y-1)) {
                                if (not add_move(board, moves, x, y, x+2, y-1) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x-2, y+1)) {
                                if (not add_move(board, moves, x, y, x-2, y+1) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x-2, y-1)) {
                                if (not add_move(board, moves, x, y, x-2, y-1) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x+1, y+2)) {
                                if (not add_move(board, moves, x, y, x+1, y+2) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x-1, y+2)) {
                                if (not add_move(board, moves, x, y, x-1, y+2) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x+1, y-2)) {
                                if (not add_move(board, moves, x, y, x+1, y-2) and not board.in_check) {
                                        b = false;
                                }
                        }

                        if (b and is_square_valid(board, x-1, y-2)) {
                                add_move(board, moves, x, y, x-1, y-2);
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> bishop(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        for (int ru = 1; x + ru < 8 and y + ru < 8; ru++) {
                                if (is_square_valid(board, x + ru, y + ru)) {
                                        if (not add_move(board, moves, x, y, x + ru, y + ru) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x + ru, y + ru) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int rd = 1; x + rd < 8 and y - rd >= 0; rd++) {
                                if (is_square_valid(board, x + rd, y - rd)) {
                                        if (not add_move(board, moves, x, y, x + rd, y - rd) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x + rd, y - rd) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int lu = 1; x - lu >= 0 and y + lu < 8; lu++) {
                                if (is_square_valid(board, x - lu, y + lu)) {
                                        if (not add_move(board, moves, x, y, x - lu, y + lu) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x - lu, y + lu) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        for (int ld = 1; x - ld >= 0 and y - ld >= 0; ld++) {
                                if (is_square_valid(board, x - ld, y - ld)) {
                                        if (not add_move(board, moves, x, y, x - ld, y - ld) and not board.in_check) {
                                                break;
                                        }
                                        if (board(x - ld, y - ld) > 0) {
                                                break;
                                        }
                                } else break;
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> queen(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        auto rook_moves = rook(board, x, y);
                        auto bishop_moves = bishop(board, x, y);

                        for (auto& m : rook_moves) {
                                moves.push_back(make_unique<GameState>(*m));
                        }

                        for (auto& m : bishop_moves) {
                                moves.push_back(make_unique<GameState>(*m));
                        }

                        return moves;
                }

                vector<unique_ptr<GameState>> king(GameState& board, int x, int y)
                {
                        vector<unique_ptr<GameState>> moves;

                        if (is_square_valid(board, x + 1, y)) {
                                add_move(board, moves, x, y, x + 1, y);
                        }

                        if (is_square_valid(board, x - 1, y)) {
                                add_move(board, moves, x, y, x - 1, y);
                        }

                        if (is_square_valid(board, x, y + 1)) {
                                add_move(board, moves, x, y, x, y + 1);
                        }

                        if (is_square_valid(board, x, y - 1)) {
                                add_move(board, moves, x, y, x, y - 1);
                        }

                        if (is_square_valid(board, x + 1, y + 1)) {
                                add_move(board, moves, x, y, x + 1, y + 1);
                        }

                        if (is_square_valid(board, x - 1, y - 1)) {
                                add_move(board, moves, x, y, x - 1, y - 1);
                        }

                        if (is_square_valid(board, x - 1, y + 1)) {
                                add_move(board, moves, x, y, x - 1, y + 1);
                        }

                        if (is_square_valid(board, x + 1, y - 1)) {
                                add_move(board, moves, x, y, x + 1, y - 1);
                        }

                        // CASTLING SHORT WHITE
                        if (is_white(board(x, y)) and board.white_castle_short) {
                                if (!board(x+1, y) and !board(x+2, y)) {
                                        add_move(board, moves, x, y, x+2, y);
                                }
                        }

                        // CASTLING LONG WHITE
                        if (is_white(board(x, y)) and board.white_castle_long) {
                                if (!board(x-1, y) and !board(x-2, y)) {
                                        add_move(board, moves, x, y, x-2, y);
                                }
                        }

                        // CASTLING SHORT BLACK
                        if (not is_white(board(x, y)) and board.black_castle_short) {
                                if (!board(x+1, y) and !board(x+2, y)) {
                                        add_move(board, moves, x, y, x+2, y);
                                }
                        }

                        // CASTLING LONG BLACK
                        if (not is_white(board(x, y)) and board.black_castle_long) {
                                if (!board(x-1, y) and !board(x-2, y)) {
                                        add_move(board, moves, x, y, x-2, y);
                                }
                        }

                        return moves;
                }
        }

        vector<unique_ptr<GameState>> moves(GameState& board, int x, int y)
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
}
