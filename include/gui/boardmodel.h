#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QTableWidgetItem>
#include "gui/pieceicon.h"
#include "game/gamestate.h"
#include "game/piecemove.h"

class BoardModel : public QAbstractTableModel
{
        Q_OBJECT
public:
        explicit BoardModel(QObject *parent, GameState gamestate);

        void select_square(int x, int y);
        void show_pieces();
        void hide_piece(int x, int y);

        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        Qt::DropActions supportedDropActions() const override;

signals:
        void player_change();

public slots:
        void cell_click(const QModelIndex& index);

private:
        bool is_white(char p);
        void clear_dots();
        void set_squares(std::unique_ptr<GameState>& gamestate);
        void set_dots(std::vector<std::unique_ptr<GameState>>& states);

        std::unique_ptr<GameState> gamestate;
        std::vector<std::unique_ptr<GameState>> potential_states;
        PieceIcon* squares[8][8] = {
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
