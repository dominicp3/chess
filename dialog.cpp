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
        connect(tableview, SIGNAL(clicked(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));
        connect(boardmodel, SIGNAL(player_change()), player_indicator, SLOT(switch_player()));

        setFixedSize(BOARD_SIZE, BOARD_SIZE);

        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);
        hboxlayout->setSpacing(0);

        tableview->setModel(boardmodel);
        tableview->setItemDelegate(new MyDelegate(this));

        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->horizontalHeader()->hide();

        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->verticalHeader()->hide();

        tableview->setFrameShape(QFrame::NoFrame);

        QSizePolicy sp_tableview(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableview->setSizePolicy(sp_tableview);
        hboxlayout->addWidget(tableview);

        QSizePolicy sp_indicator(QSizePolicy::Fixed, QSizePolicy::Expanding);
        player_indicator->setSizePolicy(sp_indicator);
        hboxlayout->addWidget(player_indicator);

        player_indicator->setFixedWidth(BORDER);
        setLayout(hboxlayout);
}
