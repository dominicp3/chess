#include "gui/pieceicon.h"

using namespace std;

PieceIcon::PieceIcon(char piece, bool dot):
        dot(dot),
        piece(piece)
{
        QString path = "images/pieces/cardinal";
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

void PieceIcon::render(QPainter* painter, const QRectF& rect)
{
        if (piece_icon.isValid() and show) {
                piece_icon.render(painter, rect);
        }

        if (dot) {
                painter->setBrush(Qt::blue);
                painter->drawEllipse(QPoint(rect.x() + rect.width()/2, rect.y() + rect.height()/2), 7, 7);
        }
}

void PieceIcon::set_dot(bool d)
{
        dot = d;
}

bool PieceIcon::get_dot()
{
        return dot;
}

void PieceIcon::set_show_piece(bool show)
{
        this->show = show;
}
