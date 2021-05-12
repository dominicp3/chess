#ifndef PIECEICON_H
#define PIECEICON_H

#include <QPainter>
#include <QSvgRenderer>

class Square : public QSvgRenderer
{
        Q_OBJECT
public:
        Square(char piece = 0, bool dot = false);

        void set_dot(bool d);
        bool get_dot();
        void set_show_piece(bool show);

public slots:
        void render(QPainter* painter, const QRectF& bounds);

private:
        QSvgRenderer piece_icon;
        bool dot = false;
        bool show = true;
};

#endif // PIECEICON_H
