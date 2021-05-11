#include "gui/boardframe.h"

using namespace std;

BoardFrame::BoardFrame(QWidget *parent):
        QFrame(parent),
        boardmodel(new BoardModel(this, GameState())),
        tableview(new MyTableView(this, boardmodel)),
        hboxlayout(new QHBoxLayout(this))
{
        setFrameShape(QFrame::NoFrame);
        connect(tableview, SIGNAL(pressed(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));
        board.load(QString("images/board/svg/brown.svg"));

        setStyleSheet("QTableView {background-color: transparent;}");

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(0, 0, 0, 0);
        hboxlayout->addWidget(tableview);

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

BoardModel* BoardFrame::get_boardmodel()
{
        return boardmodel;
}

void BoardFrame::paintEvent(QPaintEvent* event)
{
        event->accept();
        QPainter painter(this);
        board.render(&painter);
}
