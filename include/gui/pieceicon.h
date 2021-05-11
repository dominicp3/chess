#ifndef PIECEICON_H
#define PIECEICON_H

#include <QSvgRenderer>
#include <QPainter>

class PieceIcon : public QSvgRenderer
{
        Q_OBJECT
public:
        PieceIcon(char piece, bool dot);

        void set_dot(bool d);
        bool get_dot();
        void set_show_piece(bool show);

public slots:
        void render(QPainter* painter, const QRectF& bounds);

private:
        QSvgRenderer piece_icon;
        bool dot = false;
        char piece = 0;
        bool show = true;
};

#endif // PIECEICON_H
