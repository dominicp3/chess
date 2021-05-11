#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include <QHBoxLayout>
#include "game/gamestate.h"
#include "gui/boardmodel.h"
#include "gui/mytableview.h"

class BoardFrame : public QFrame
{
        Q_OBJECT
public:
        explicit BoardFrame(QWidget *parent = nullptr);

        BoardModel* get_boardmodel();
        void paintEvent(QPaintEvent* event) override;

private:
        BoardModel* boardmodel;
        MyTableView* tableview;
        QSvgRenderer board;
        QHBoxLayout* hboxlayout;
};

#endif // BOARDFRAME_H
