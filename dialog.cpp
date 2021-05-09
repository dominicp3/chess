#include "dialog.h"

using namespace std;

enum CONSTANTS {
        BOARD_SIZE = 650,
        BORDER = 22
};

Dialog::Dialog(QWidget* parent):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        tableview(new QTableView(this)),
        boardmodel(new BoardModel(tableview, GameState())),
        player_indicator(new Indicator(this))
{
        connect(tableview, SIGNAL(clicked(QModelIndex)), this, SLOT(cell_click(QModelIndex)));
        connect(boardmodel, SIGNAL(player_change()), player_indicator, SLOT(switch_player()));

        setFixedSize(BOARD_SIZE, BOARD_SIZE);

        tableview->setModel(boardmodel);
        tableview->setItemDelegate(new MyDelegate);

        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->horizontalHeader()->hide();
        tableview->verticalHeader()->hide();
        tableview->setFrameShape(QFrame::NoFrame);

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);

        QSizePolicy sp_tableview(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableview->setSizePolicy(sp_tableview);
        hboxlayout->addWidget(tableview);

        QSizePolicy sp_indicator(QSizePolicy::Fixed, QSizePolicy::Expanding);
        player_indicator->setSizePolicy(sp_indicator);

        player_indicator->setFixedWidth(BORDER);
        hboxlayout->addWidget(player_indicator);
        hboxlayout->setSpacing(0);

        setLayout(hboxlayout);
}

void Dialog::cell_click(const QModelIndex &index)
{
        boardmodel->select_square(index.column(), 7-index.row());
}
