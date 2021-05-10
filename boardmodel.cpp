#include "boardmodel.h"
#include <iostream>

using namespace std;

BoardModel::BoardModel(QObject* parent, GameState gamestate):
        QAbstractTableModel(parent),
        gamestate(make_unique<GameState>(gamestate))
{
        set_squares(this->gamestate);
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

QModelIndex BoardModel::parent(const QModelIndex& index) const
{
        Q_UNUSED(index);
        return QModelIndex();
}

Qt::ItemFlags BoardModel::flags(const QModelIndex& index) const
{
        Qt::ItemFlags default_flags = QAbstractTableModel::flags(index);

        if (index.isValid()) {
                return Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | default_flags;
        }

        return Qt::ItemIsDropEnabled | default_flags;
}

Qt::DropActions BoardModel::supportedDropActions() const
{
        return Qt::MoveAction | Qt::CopyAction;
}

void BoardModel::set_dots(std::vector<std::unique_ptr<GameState>>& states)
{
        for (auto& state : states) {
                pair<int, int> sq = state->current_move;
                squares[sq.first][sq.second]->set_dot(true);
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

        emit this->dataChanged(QModelIndex(), QModelIndex());
}

void BoardModel::drop_square(int x, int y)
{
        if ((*gamestate)(x, y) == 0) {
                select_square(x, y);
                return;
        }

        clear_dots();
}

void BoardModel::select_square(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8) {
                return;
        }

        char p = (*gamestate)(x, y);
        clear_dots();

        if (p > 0 and is_white(p) == gamestate->white_to_move) {
                potential_states = piecemove::moves(*gamestate, x, y);
                set_dots(potential_states);
                emit this->dataChanged(QModelIndex(), QModelIndex());
                return;
        }

        for (auto& state : potential_states) {
                if (make_pair(x, y) == state->current_move) {
                        gamestate = move(state);
                        set_squares(gamestate);
                        emit player_change();
                        emit this->dataChanged(QModelIndex(), QModelIndex());
                        break;
                }
        }

        potential_states.clear();
}

bool BoardModel::is_white(char p)
{
        return (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k');
}

void BoardModel::cell_click(const QModelIndex& index)
{
        select_square(index.column(), 7 - index.row());
}

void BoardModel::set_squares(unique_ptr<GameState>& gamestate)
{
        bool white = false;
        for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                        delete squares[x][y];
                        squares[x][y] = new Square(white, (*gamestate)(x, y), false);
                        white = not white;
                }

                white = not white;
        }
}
