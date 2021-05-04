#include "computer.h"

Computer::Computer()
{

}

//vector<shared_ptr<GameState>> Computer::actions(GameState& board, char player)
//{
//        vector<shared_ptr<Board>> actions;

//        if (player == 'w') {
//                for (auto& p : board.get_white_pieces()) {

//                        vector<pair<int, int>> moves = board.legal_moves(p->x(), p->y());

//                        for (pair<int, int> m : moves) {
//                                shared_ptr<Board> new_board = make_shared<Board>(board);
//                                new_board->move_piece(p->x(), p->y(), m.first, m.second);
//                                actions.push_back(new_board);
//                        }
//                }
//        }

//        if (player == 'b') {
//                for (auto& p : board.get_black_pieces()) {
//                        vector<pair<int, int>> moves = board.legal_moves(p->x(), p->y());

//                        for (pair<int, int> m : moves) {
//                                shared_ptr<Board> new_board = make_shared<Board>(board);
//                                new_board->move_piece(p->x(), p->y(), m.first, m.second);
//                                actions.push_back(new_board);

//                        }
//                }
//        }

//        return actions;
//}

//void Computer::next_move()
//{
//        int depth = 2;

//        int value = 0;

//        if (m_gamestate.white_to_move == 'w') {
//                value = INT_MIN;
//                for (auto& b : actions(m_board, m_gamestate.white_to_move)) {
//                        if (minimax(b, depth, INT_MIN, INT_MAX, 'b') > value) {
//                                m_board = Board(*b);
//                        }
//                }
//        }

//        if (m_gamestate.white_to_move == 'b') {
//                value = INT_MAX;
//                for (auto& b : actions(m_board, m_gamestate.white_to_move)) {
//                        if (minimax(b, depth, INT_MIN, INT_MAX, 'w') < value) {
//                                m_board = Board(*b);
//                        }
//                }
//        }

////        cout << "VALUE = " << value << endl;
//}

//int Computer::minimax(shared_ptr<GameState> node, int depth, int alpha, int beta, char player)
//{

//        if (depth <= 0 or node->checkmate(player)) {
//                return node->evaluate();
//        }

////        node->print_board();

//        int value = 0;

//        if (player == 'w') {

//                auto moves = actions(*node, 'w');

//                value = INT_MIN;
//                for (auto &b : moves) {
//                        value = max(value, minimax(b, depth - 1, alpha, beta, 'b'));
//                        alpha = max(alpha, value);
//                        if (alpha >= beta) {
//                                break;
//                        }
//                }
//        }

//        if (player == 'b') {

//                auto moves = actions(*node, 'b');

//                value = INT_MAX;
//                for (auto &b : moves) {
//                        value = min(value, minimax(b, depth - 1, alpha, beta, 'w'));
//                        beta = min(alpha, value);
//                        if (beta <= alpha) {
//                                break;
//                        }
//                }
//        }

//        return value;
//}
