#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include "hash.h"

typedef std::unordered_map<std::pair<int, int>, char, pair_hash> piece_map;

struct GameState
{
        GameState() {}
        GameState(piece_map& pieces, bool player);
        char operator()(int x, int y);
        char operator()(std::pair<int, int> coord);
        void move_piece(int ox, int oy, int nx, int ny);

        std::pair<int, int> current_move = {-1, -1};

        std::pair<int, int> white_king_coord = {4, 0};
        std::pair<int, int> black_king_coord = {4, 7};

        // HASHMAP: key = std::pair<int, int>, value = char
        // lowercase = white piece, uppercase = black piece
        piece_map white_pieces =
        {
                {{0, 1}, 'p'}, {{1, 1}, 'p'}, {{2, 1}, 'p'}, {{3, 1}, 'p'}, {{4, 1}, 'p'}, {{5, 1}, 'p'}, {{6, 1}, 'p'}, {{7, 1}, 'p'},
                {{0, 0}, 'r'}, {{1, 0}, 'n'}, {{2, 0}, 'b'}, {{3, 0}, 'q'}, {white_king_coord, 'k'}, {{5, 0}, 'b'}, {{6, 0}, 'n'}, {{7, 0}, 'r'}
        };

        piece_map black_pieces =
        {
                {{0, 7}, 'R'}, {{1, 7}, 'N'}, {{2, 7}, 'B'}, {{3, 7}, 'Q'}, {black_king_coord, 'K'}, {{5, 7}, 'B'}, {{6, 7}, 'N'}, {{7, 7}, 'R'},
                {{0, 6}, 'P'}, {{1, 6}, 'P'}, {{2, 6}, 'P'}, {{3, 6}, 'P'}, {{4, 6}, 'P'}, {{5, 6}, 'P'}, {{6, 6}, 'P'}, {{7, 6}, 'P'}
        };

        bool white_to_move = true;

        bool white_castle_short = true;
        bool white_castle_long = true;

        bool black_castle_short = true;
        bool black_castle_long = true;

        bool in_check = false;

        bool en_passant_white = false; // white can execute en passant
        bool en_passant_black = false;

        bool en_passant = false; // flag to say en passant is being executed this move
};
#endif // GAMESTATE_H
