#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QTableWidgetItem>
#include "square.h"
#include "gamestate.h"
#include "piecemove.h"

class BoardModel : public QAbstractTableModel
{
public:
        explicit BoardModel(QObject *parent, GameState gamestate);
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        void set_dots(std::vector<std::unique_ptr<GameState>>& states);
        void clear_dots();
        void select_square(int x, int y);

        bool is_white(char p);

private:
        void set_squares(std::unique_ptr<GameState>& gamestate);

        std::unique_ptr<GameState> gamestate;
        std::vector<std::unique_ptr<GameState>> potential_states;
        Square* squares[8][8] = {
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
        };
};

#endif // BOARDMODEL_H