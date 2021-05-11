#include "gui/boardframe.h"

using namespace std;

BoardFrame::BoardFrame(QWidget *parent):
        QFrame(parent),
        hboxlayout(new QHBoxLayout(this)),
        tableview(new MyTableView(this, new BoardModel(this, GameState())))
{
        setFrameShape(QFrame::NoFrame);
        board_image.load(QString("images/board/svg/brown.svg"));

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

MyTableView*& BoardFrame::get_tableview()
{
        return tableview;
}
