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
