#ifndef GRID_H
#define GRID_H

#include <QSvgWidget>
#include <QSvgRenderer>
#include <QPainter>
#include <QWidget>
#include <QPixmap>
#include <QTableWidgetItem>
#include <QAbstractItemModel>
#include <QVariant>
#include <QDir>
#include <QWidget>
#include <vector>
#include <QModelIndex>
#include "square.h"
#include "gamestate.h"

class Grid : public QAbstractTableModel
{
public:
        explicit Grid(QObject *parent, GameState& gamestate);
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        void set_dot(bool d, int x, int y);

private:
        void setup(bool white, char piece);
        std::vector<std::vector<Square*>> grid = {
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };

        QPixmap* pm = new QPixmap("images/wQ.svg");
};

#endif // GRID_H
