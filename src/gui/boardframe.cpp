#include "gui/boardframe.h"

using namespace std;

BoardFrame::BoardFrame(QWidget *parent, GameState& gamestate):
        QFrame(parent),
        hboxlayout(new QHBoxLayout(this)),
        tableview(new QTableView(this))
{
        BoardModel* boardmodel = new BoardModel(this, gamestate);
        connect(tableview, SIGNAL(pressed(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));

        tableview->setModel(boardmodel);

        tableview->setShowGrid(false);
        tableview->setFrameShape(QFrame::NoFrame);

        tableview->setModel(boardmodel);
        tableview->setItemDelegate(new MyDelegate(this));

        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->horizontalHeader()->hide();

        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->verticalHeader()->hide();

        tableview->setDragDropMode(QAbstractItemView::InternalMove);


        setFrameShape(QFrame::NoFrame);
        board_image.load(QString("images/board/svg/green.svg"));

        setStyleSheet("QTableView {background-color: transparent;}");

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(0, 0, 0, 0);
        hboxlayout->addWidget(tableview);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        setLayout(hboxlayout);
}

void BoardFrame::paintEvent(QPaintEvent* event)
{
        event->accept();
        QPainter painter(this);
        board_image.render(&painter);
}

QTableView*& BoardFrame::get_tableview()
{
        return tableview;
}
