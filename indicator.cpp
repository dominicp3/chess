#include "indicator.h"

using namespace std;

Indicator::Indicator(QWidget* parent):
        QWidget(parent) {}

void Indicator::paintEvent(QPaintEvent* event)
{
        QPainter painter(this);
        painter.setBrush(Qt::white);
        int h = top ? this->width() + 5 : this->height() - this->width() - 5;
        painter.drawEllipse(QPoint(this->width()/2, h), 5, 5);
}

void Indicator::switch_player()
{
        top = not top;
        update();
}
