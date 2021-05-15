#include "game/gamestate.h"

using namespace std;

GameState::GameState() {}

GameState::GameState(piece_map& pieces, bool player): white_to_move(player)
{
        for (auto it = pieces.begin(); it != pieces.end(); it++) {

                pair<int, int> coord = it->first;
                char p = it->second;

                if (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k') {
                        white_pieces[coord] = p;
                }

                if (p == 'P' or p == 'R' or p == 'N' or p == 'B' or p == 'Q' or p == 'K') {
                        black_pieces[coord] = p;
                }
        }
}

char GameState::operator()(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8) {
                return -1;
        }

        if (white_pieces.find({x, y}) != white_pieces.end()) {
                return white_pieces.at({x, y});
        }

        if (black_pieces.find({x, y}) != black_pieces.end()) {
                return black_pieces.at({x, y});
        }

        return 0;
}

char GameState::operator()(pair<int, int> coord)
{
        return operator()(coord.first, coord.second);
}

void GameState::move_piece(int ox, int oy, int nx, int ny)
{
        if (ox == nx and oy == ny) {
                return;
        }

        if (white_pieces.find({ox, oy}) != white_pieces.end()) {
                char p = white_pieces.at({ox, oy});
                if (p == 'k') {
                        white_king_coord = {nx, ny};
                        white_castle_short = false;
                        white_castle_long = false;
                }

                if (p == 'r') {
                        if (ox == 0)
                                white_castle_long = false;
                        if (ox == 7)
                                white_castle_short = false;
                }

                white_pieces[{nx, ny}] = p;
                white_pieces.erase({ox, oy});

                if (black_pieces.find({nx, ny}) != black_pieces.end()) {
                        if (black_pieces.at({nx, ny}) == 'K') {
                                black_king_coord = {-1, -1};
                        }
                        black_pieces.erase({nx, ny});
                }

                current_move = {nx, ny};
        }

        if (black_pieces.find({ox, oy}) != black_pieces.end()) {
                char p = black_pieces.at({ox, oy});
                if (p == 'K') {
                        black_king_coord = {nx, ny};
                        black_castle_short = false;
                        black_castle_long = false;
                }

                if (p == 'R') {
                        if (ox == 0)
                                black_castle_long = false;
                        if (ox == 7)
                                black_castle_short = false;
                }

                black_pieces[{nx, ny}] = p;
                black_pieces.erase({ox, oy});

                if (white_pieces.find({nx, ny}) != white_pieces.end()) {
                        if (white_pieces.at({nx, ny}) == 'k') {
                                white_king_coord = {-1, -1};
                        }
                        white_pieces.erase({nx, ny});
                }

                current_move = {nx, ny};
        }
}
