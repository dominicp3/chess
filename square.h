#ifndef SQUARE_H
#define SQUARE_H

#include <QSvgRenderer>
#include <QPainter>

class Square : public QObject
{
        Q_OBJECT
public:
        Square(bool white = false, char piece = 0, bool dot = false);

        void render(QPainter* paint, QRect rect);
        void set_dot(bool d);
        bool get_dot();

private:
        QSvgRenderer piece_icon;
        bool white = false;
        bool dot = false;
};

#endif // SQUARE_H
