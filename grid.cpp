#include "grid.h"
#include <iostream>

using namespace std;

Grid::Grid(QObject* parent, GameState& gamestate):
        QAbstractTableModel(parent)
{
        bool white = false;
        for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                        grid[x][y] = new Square(white, gamestate(x, y));
                        white = not white;
                }

                white = not white;
        }
}

int Grid::columnCount(const QModelIndex& parent) const
{
        return 8;
}

int Grid::rowCount(const QModelIndex& parent) const
{
        return 8;
}

QVariant Grid::data(const QModelIndex& index, int role) const
{
        QVariant v;
        v.setValue(grid[index.column()][7-index.row()]);
        return v;
}

QModelIndex Grid::index(int row, int column, const QModelIndex& parent) const
{
        return createIndex(row, column, grid[row][column]);
}

QModelIndex Grid::parent(const QModelIndex& index) const
{
        return QModelIndex();
}

bool Grid::setData(const QModelIndex& index, const QVariant& value, int role)
{

}

void Grid::set_dot(bool d, int x, int y)
{
        grid[x][y]->set_dot(d);
}

