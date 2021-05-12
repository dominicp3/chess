#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include <QHBoxLayout>
#include <QPaintEvent>
#include "game/gamestate.h"
#include "gui/boardmodel.h"
#include "gui/mytableview.h"

class BoardFrame : public QFrame
{
        Q_OBJECT
public:
        explicit BoardFrame(QWidget *parent = nullptr);
        MyTableView*& get_tableview();

protected:
        void paintEvent(QPaintEvent* event) override;

private:
        QHBoxLayout* hboxlayout;
        MyTableView* tableview;
        QSvgRenderer board_image;
};

#endif // BOARDFRAME_H
