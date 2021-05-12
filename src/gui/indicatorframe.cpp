#include "gui/indicatorframe.h"

using namespace std;

IndicatorFrame::IndicatorFrame(QWidget* parent, bool top):
        QWidget(parent),
        top(top)
{
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        setFixedWidth(BORDER);
}

void IndicatorFrame::paintEvent(QPaintEvent* event)
{
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setBrush(Qt::white);
        int h = top ? this->width() + 5 : this->height() - this->width() - 5;
        painter.drawEllipse(QPoint(this->width()/2, h), 5, 5);
}


void IndicatorFrame::switch_player()
{
        top = not top;
        update();
}
