#include "gui/pieceicon.h"

using namespace std;

PieceIcon::PieceIcon(char piece, bool dot):
        dot(dot),
        piece(piece)
{
        QString path = "images/pieces/cardinal";

        switch (piece) {
        case 'p': piece_icon.load(path + "/wP.svg");
                  break;
        case 'n': piece_icon.load(path + "/wN.svg");
                  break;
        case 'b': piece_icon.load(path + "/wB.svg");
                  break;
        case 'r': piece_icon.load(path + "/wR.svg");
                  break;
        case 'q': piece_icon.load(path + "/wQ.svg");
                  break;
        case 'k': piece_icon.load(path + "/wK.svg");
                  break;

        case 'P': piece_icon.load(path + "/bP.svg");
                  break;
        case 'N': piece_icon.load(path + "/bN.svg");
                  break;
        case 'B': piece_icon.load(path + "/bB.svg");
                  break;
        case 'R': piece_icon.load(path + "/bR.svg");
                  break;
        case 'Q': piece_icon.load(path + "/bQ.svg");
                  break;
        case 'K': piece_icon.load(path + "/bK.svg");
                  break;
        default: break;
        }

        setAspectRatioMode(Qt::KeepAspectRatio);
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
