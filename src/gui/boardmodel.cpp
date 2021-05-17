#include "gui/boardmodel.h"

using namespace std;

BoardModel::BoardModel(QObject* parent, GameState& gamestate):
        QAbstractTableModel(parent),
        current_state(make_unique<GameState>(gamestate))
{
        sync_squares();
}

int BoardModel::columnCount(const QModelIndex& parent) const
{
        Q_UNUSED(parent);
        return 8;
}

int BoardModel::rowCount(const QModelIndex& parent) const
{
        Q_UNUSED(parent);
        return 8;
}

QVariant BoardModel::data(const QModelIndex& index, int role) const
{
        Q_UNUSED(role);
        QVariant v;
        v.setValue(squares[index.column()][7-index.row()]);
        return v;
}

QModelIndex BoardModel::index(int row, int column, const QModelIndex& parent) const
{
        Q_UNUSED(parent);
        return createIndex(row, column, squares[column][7-row]);
}

void BoardModel::select_square(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8) {
                return;
        }

        if (square_selected) {
                execute_move(x, y);
        }

        if (not square_selected) {
                possible_moves(x, y);
        }

        emit this->dataChanged(QModelIndex(), QModelIndex());
}

void BoardModel::cell_click(const QModelIndex& index)
{
        select_square(index.column(), 7-index.row());
}

void BoardModel::possible_moves(int x, int y)
{
        char p = (*current_state)(x, y);
        bool white = (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k');
        if (p > 0 and white == current_state->white_to_move) {
                potential_states = piecemove::moves(*current_state, x, y);
                for (auto& state : potential_states) {
                        squares[state->current_move.first][state->current_move.second]->set_dot(true);
                }
                square_selected = true;
        }
}

void BoardModel::execute_move(int x, int y)
{
        for (auto& state : potential_states) {
                if (state->current_move == make_pair(x, y)) {
                        current_state = move(state);
                        sync_squares();
                        potential_states.clear();
                        emit player_change();
                        break;
                }
        }

        square_selected = false;
        clear_dots();
}

void BoardModel::sync_squares()
{
        bool white = false;
        for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                        delete squares[x][y];
                        squares[x][y] = new Square((*current_state)(x, y), false, white);
                        white = not white;
                }
                white = not white;
        }
}

void BoardModel::clear_dots()
{
        for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                        if (squares[x][y]) {
                                squares[x][y]->set_dot(false);
                        }
                }
        }
}
