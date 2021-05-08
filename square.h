#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QPainter>

class Square : public QObject
{
        Q_OBJECT
public:
        Square(bool white = false, char piece = 0);

        void render(QPainter* paint, QRect rect);
        void set_dot(bool d);

private:
        QSvgRenderer piece_icon;
        bool dot = false;
        bool white = false;
};

#endif // SQUARE_H
