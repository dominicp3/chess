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

        void add_move(GameState& board, std::vector<std::unique_ptr<GameState>>& moves, int ox, int oy, int nx, int ny);
        void castling(GameState& board, std::vector<std::unique_ptr<GameState>>& moves, bool white, bool castle_short);

        std::vector<std::unique_ptr<GameState>> pawn_w(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> pawn_b(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> rook(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> knight(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> bishop(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> queen(GameState& board, int x, int y);
        std::vector<std::unique_ptr<GameState>> king(GameState& board, int x, int y);

        bool piece_check(GameState& board, int x, int y);
        bool pawn_check(GameState& board, int x, int y);
        bool rook_check(GameState& board, int x, int y);
        bool knight_check(GameState& board, int x, int y);
        bool bishop_check(GameState& board, int x, int y);
        bool queen_check(GameState& board,int x, int y);
        bool king_check(GameState& board, int x, int y);

        bool in_check(GameState& board);
};

#endif // PIECEMOVE_H
