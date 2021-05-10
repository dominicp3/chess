#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QTableWidgetItem>
#include "square.h"
#include "gamestate.h"
#include "piecemove.h"

class BoardModel : public QAbstractTableModel
{
        Q_OBJECT
public:
        explicit BoardModel(QObject *parent, GameState gamestate);
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        Qt::DropActions supportedDropActions() const override;

        void set_dots(std::vector<std::unique_ptr<GameState>>& states);
        void clear_dots();

        void drop_square(int x, int y);
        void select_square(int x, int y);

        bool is_white(char p);

signals:
        void player_change();

private slots:
        void cell_click(const QModelIndex& index);

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
