#include "dialog.h"

using namespace std;

enum CONSTANTS {
        BOARD_SIZE = 650
};

Dialog::Dialog(QWidget *parent):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        tableview(new QTableView(this)),
        boardmodel(new BoardModel(tableview, GameState()))
{
        connect(tableview, SIGNAL(clicked(QModelIndex)), this, SLOT(cell_click(QModelIndex)));

        setFixedSize(BOARD_SIZE, BOARD_SIZE);

        tableview->setModel(boardmodel);
        tableview->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        tableview->setItemDelegate(new MyDelegate);

        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->horizontalHeader()->hide();
        tableview->verticalHeader()->hide();
        tableview->setFrameShape(QFrame::NoFrame);

        hboxlayout->addWidget(tableview);

        setLayout(hboxlayout);
}

void Dialog::cell_click(const QModelIndex &index)
{
        boardmodel->select_square(index.column(), 7-index.row());
}
