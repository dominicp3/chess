#include "gui/mytableview.h"

using namespace std;

MyTableView::MyTableView(QWidget* parent, BoardModel* boardmodel):
        QTableView(parent)
{
        connect(this, SIGNAL(pressed(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));

        setShowGrid(false);
        setFrameShape(QFrame::NoFrame);

        setModel(boardmodel);
        setItemDelegate(new MyDelegate(this));

        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        horizontalHeader()->hide();

        verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        verticalHeader()->hide();

        setDragDropMode(QAbstractItemView::InternalMove);
}

void MyTableView::dragEnterEvent(QDragEnterEvent* event)
{
        event->accept();
        if (!(event->possibleActions() & (Qt::CopyAction | Qt::MoveAction))) {
                return;
        }

        int x = columnAt(event->pos().x());
        int y = 7-rowAt(event->pos().y());

        if (not outside) {
                static_cast<BoardModel*>(model())->hide_piece(x, y);
                static_cast<BoardModel*>(model())->select_square(x, y);
        }

        outside = false;
}

void MyTableView::dragMoveEvent(QDragMoveEvent* event)
{
        event->accept();
}

void MyTableView::dragLeaveEvent(QDragLeaveEvent* event)
{
        event->accept();
        outside = true;
}

void MyTableView::dropEvent(QDropEvent* event)
{
        event->accept();
        int x = columnAt(event->pos().x());
        int y = 7-rowAt(event->pos().y());
        static_cast<BoardModel*>(model())->select_square(x, y);
        static_cast<BoardModel*>(model())->show_pieces();
}
