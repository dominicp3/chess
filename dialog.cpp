#include "dialog.h"
#include <iostream>

using namespace std;

enum CONSTANTS {
        BORDER = 22,
        WIDTH = 500,
        HEIGHT = 500
};

Dialog::Dialog(QWidget* parent):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        boardmodel(new BoardModel(this, GameState())),
        tableview(new MyTableView(this, boardmodel)),
        player_indicator(new Indicator(this))
{
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect mm = screen->availableGeometry() ;
        int size = mm.width() / 3.5;

        resize(size, size);

        connect(tableview, SIGNAL(pressed(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));
        connect(boardmodel, SIGNAL(player_change()), player_indicator, SLOT(switch_player()));

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);
        hboxlayout->addWidget(tableview);
        hboxlayout->addWidget(player_indicator);

        setMinimumSize(size, size);

        setLayout(hboxlayout);
        show();
}

void Dialog::mousePressEvent(QMouseEvent* event)
{
        if (event->button() != Qt::LeftButton) {
                return;
        }

        startpos = event->pos();
}

void Dialog::mouseMoveEvent(QMouseEvent* event)
{
        if (!(event->buttons() & Qt::LeftButton)) {
                return;
        }

        if ((event->pos() - startpos).manhattanLength() < QApplication::startDragDistance()) {
                return;
        }

        QDrag* drag = new QDrag(this);
        drag->exec(Qt::CopyAction | Qt::MoveAction);
}
