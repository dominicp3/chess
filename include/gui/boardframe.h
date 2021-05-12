#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include <QHBoxLayout>
#include <QPaintEvent>
#include <QHeaderView>
#include "game/gamestate.h"
#include "gui/boardmodel.h"
#include "gui/mydelegate.h"

class BoardFrame : public QFrame
{
        Q_OBJECT
public:
        explicit BoardFrame(QWidget *parent, GameState& gamestate);
        QTableView*& get_tableview();
protected:
        void paintEvent(QPaintEvent* event) override;

private:
        QHBoxLayout* hboxlayout;
        QTableView* tableview;
        QSvgRenderer board_image;
};

#endif // BOARDFRAME_H
