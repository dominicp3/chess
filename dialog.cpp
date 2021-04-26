#include "dialog.h"
#include "ui_dialog.h"
#include "board.h"
#include <iostream>

Dialog::Dialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog),
        timer(new QTimer(this))
{
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        timer->start(20);
        setFixedSize(626, 626);
        ui->setupUi(this);
}

Dialog::~Dialog()
{
        delete ui;
}

void Dialog::nextFrame()
{
        update();
}

void Dialog::paintEvent(QPaintEvent *event)
{
        QPainter paint {this};
        QPixmap boardImage {QDir::currentPath().append("/images/board.jpg")};
        paint.drawPixmap(0, 0, boardImage);

        game.render(paint);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
        int x = (event->x() - 36) / 69;
        int y = 7 - ((event->y() - 36) / 69);

        game.select_square(x, y);
}
