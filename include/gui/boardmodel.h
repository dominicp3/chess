#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QTableWidgetItem>
#include "gui/square.h"
#include "game/gamestate.h"
#include "game/piecemove.h"

class BoardModel : public QAbstractTableModel
{
        Q_OBJECT
public:
        explicit BoardModel(QObject *parent, GameState gamestate);

        void select_square(int x, int y);

        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

signals:
        void player_change();

public slots:
        void cell_click(const QModelIndex& index);

private:
        void possible_moves(int x, int y);
        void execute_move(int x, int y);
        void sync_squares();
        void clear_dots();

        bool square_selected = false;

        std::unique_ptr<GameState> current_state;
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
