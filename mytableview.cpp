#include "mytableview.h"
#include <iostream>
#include <QApplication>
#include <QDrag>

using namespace std;

MyTableView::MyTableView(QWidget* parent, BoardModel* boardmodel):
        QTableView(parent)
{
        setModel(boardmodel);
        setItemDelegate(new MyDelegate(this));

        resizeRowsToContents();
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        horizontalHeader()->hide();

        resizeColumnsToContents();
        verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        verticalHeader()->hide();

        setFrameShape(QFrame::NoFrame);

        setDragEnabled(true);
        setAcceptDrops(true);
        setDragDropMode(QAbstractItemView::InternalMove);
}

void MyTableView::dragEnterEvent(QDragEnterEvent* event)
{
        event->accept();
        int x = this->currentIndex().column();
        int y = 7 - this->currentIndex().row();
        static_cast<BoardModel*>(model())->select_square(x, y);
}

void MyTableView::dragMoveEvent(QDragMoveEvent* event)
{
        event->accept();
}

void MyTableView::dropEvent(QDropEvent* event)
{
        event->accept();
        int x = columnAt(event->pos().x());
        int y = 7-rowAt(event->pos().y());
        static_cast<BoardModel*>(model())->drop_square(x, y);
}
