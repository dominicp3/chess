#include "engine.h"

using namespace std;

Engine::Engine()
{

}

vector<unique_ptr<GameState>> Engine::actions(GameState& board)
{
        vector<unique_ptr<GameState>> actions;
        piece_map& pieces = board.white_to_move ? board.white_pieces : board.black_pieces;

        for (auto p = pieces.begin(); p != pieces.end(); p++) {
                auto m = piece_move.moves(board, p->first.first, p->first.second);
                actions.insert(actions.end(), make_move_iterator(m.begin()), make_move_iterator(m.end()));
        }

        return actions;
}

std::unique_ptr<GameState> Engine::next_move(GameState& board)
{
        int depth = 2;
        int value;

        unique_ptr<GameState> result;

        if (board.white_to_move) {
                value = numeric_limits<int>::min();
                for (auto& b : actions(board)) {
                        if (minimax(*b, depth, numeric_limits<int>::min(), numeric_limits<int>::max()) > value) {
                                result = move(b);
                        }
                }
        } else {
                value = numeric_limits<int>::max();
                for (auto& b : actions(board)) {
                        if (minimax(*b, depth, numeric_limits<int>::min(), numeric_limits<int>::max()) < value) {
                                result = move(b);
                        }
                }
        }

        return result;
}

int Engine::minimax(GameState& node, int depth, int alpha, int beta)
{
        if (depth <= 0) {
                return evaluate(node);
        }

        int value = 0;

        if (node.white_to_move) {
                auto moves = actions(node);

                // BLACK IS IN CHECKMATE
                if (node.in_check and moves.size() == 0) {
                        return evaluate(node) - 100;
                }

                value = numeric_limits<int>::min();
                for (auto& b : moves) {
                        value = max(value, minimax(*b, depth - 1, alpha, beta));
                        alpha = max(alpha, value);
                        if (alpha >= beta) {
                                break;
                        }
                }
        } else {
                auto moves = actions(node);

                // WHITE IS IN CHECKMATE
                if (node.in_check and moves.size() == 0) {
                        return evaluate(node) + 100;
                }

                value = numeric_limits<int>::max();
                for (auto& b : moves) {
                        value = min(value, minimax(*b, depth - 1, alpha, beta));
                        beta = min(alpha, value);
                        if (beta <= alpha) {
                                break;
                        }
                }
        }

        return value;
}

int Engine::evaluate(GameState &board)
{
        int value = 0;

        for (auto p = board.white_pieces.begin(); p != board.white_pieces.end(); p++) {
                value += piece_value[p->second];
        }

        return value;
}
