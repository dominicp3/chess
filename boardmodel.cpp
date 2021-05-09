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
        return 8;
}

int BoardModel::rowCount(const QModelIndex& parent) const
{
        return 8;
}

QVariant BoardModel::data(const QModelIndex& index, int role) const
{
        QVariant v;
        v.setValue(squares[index.column()][7-index.row()]);
        return v;
}

QModelIndex BoardModel::index(int row, int column, const QModelIndex& parent) const
{
        return createIndex(row, column, squares[column][7-row]);
}

QModelIndex BoardModel::parent(const QModelIndex& index) const
{
        return QModelIndex();
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
}

bool BoardModel::is_white(char p)
{
        return (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k');
}

void BoardModel::cell_click(const QModelIndex& index)
{
        int x = index.column();
        int y = 7 - index.row();

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
                        break;
                }
        }

        emit this->dataChanged(QModelIndex(), QModelIndex());
        potential_states.clear();
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
