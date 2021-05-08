#include "square.h"
#include <iostream>

using namespace std;

Square::Square(bool white, char piece):
        white(white)
{
        QString path = "pieces/cardinal";
        switch (piece) {
        case 'p': path += "/wP.svg";
                  break;
        case 'n': path += "/wN.svg";
                  break;
        case 'b': path += "/wB.svg";
                  break;
        case 'r': path += "/wR.svg";
                  break;
        case 'q': path += "/wQ.svg";
                  break;
        case 'k': path += "/wK.svg";
                  break;

        case 'P': path += "/bP.svg";
                  break;
        case 'N': path += "/bN.svg";
                  break;
        case 'B': path += "/bB.svg";
                  break;
        case 'R': path += "/bR.svg";
                  break;
        case 'Q': path += "/bQ.svg";
                  break;
        case 'K': path += "/bK.svg";
                  break;
        default: break;
        }
        piece_icon.load(path);
}

void Square::render(QPainter* paint, QRect rect)
{
        if (white) {
                paint->fillRect(rect, Qt::white);
        } else {
                paint->fillRect(rect, Qt::darkGreen);
        }

        if (piece_icon.isValid()) {
                piece_icon.render(paint, rect);
        }

        if (dot) {
                paint->setBrush(Qt::blue);
                paint->drawEllipse(QPoint(rect.width()/2, rect.height()/2), 7, 7);
        }
}

void Square::set_dot(bool d)
{
        dot = d;
}
