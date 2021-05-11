#include "gui/mytableview.h"

using namespace std;

MyTableView::MyTableView(QWidget* parent, BoardModel* boardmodel):
        QTableView(parent)
{
        setModel(boardmodel);
        setItemDelegate(new MyDelegate(this));

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setAutoFillBackground(true);

        resizeRowsToContents();
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        horizontalHeader()->hide();

        resizeColumnsToContents();
        verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        verticalHeader()->hide();

        setFrameShape(QFrame::NoFrame);

        setDragDropMode(QAbstractItemView::InternalMove);
}

void MyTableView::dragEnterEvent(QDragEnterEvent* event)
{
        event->accept();
        int x = columnAt(event->pos().x());
        int y = 7-rowAt(event->pos().y());
        pos = QPoint(x, y);
        static_cast<BoardModel*>(model())->select_square(x, y);
        static_cast<BoardModel*>(model())->set_show_piece(x, y, false);

}

void MyTableView::dragMoveEvent(QDragMoveEvent* event)
{
        event->accept();
}

void MyTableView::dragLeaveEvent(QDragLeaveEvent* event)
{
        event->accept();
        static_cast<BoardModel*>(model())->set_show_piece(pos.x(), pos.y(), true);
}

void MyTableView::dropEvent(QDropEvent* event)
{
        event->accept();
        int x = columnAt(event->pos().x());
        int y = 7-rowAt(event->pos().y());
        static_cast<BoardModel*>(model())->drop_square(x, y);
        static_cast<BoardModel*>(model())->set_show_piece(pos.x(), pos.y(), true);
}
