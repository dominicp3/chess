#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include "gamestate.h"
#include <vector>
#include <memory>

class PieceMove
{
public:
        std::vector<std::unique_ptr<GameState>> moves(GameState& board, int x, int y);

private:
        int is_white(char p);
        bool is_square_valid(GameState& board, int x, int y);
        void add_move_legal(GameState& board, std::vector<std::unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny);

        std::vector<std::pair<int, int>> squares(GameState& board, int x, int y);

        void castling(GameState& board, std::vector<std::unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny);

        std::vector<std::pair<int, int>> pawn_w(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> pawn_b(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> rook(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> knight(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> bishop(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> queen(GameState& board, int x, int y);
        std::vector<std::pair<int, int>> king(GameState& board, int x, int y);

        std::vector<std::unique_ptr<GameState>> pawn_w_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> pawn_b_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> rook_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> knight_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> bishop_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> queen_legal(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> king_legal(GameState& board, int x, int y);

        bool is_white_in_check(GameState& board);
        bool is_black_in_check(GameState& board);
};

#endif // PIECEMOVE_H
