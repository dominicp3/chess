#include "gui/square.h"

using namespace std;

Square::Square(char piece, bool dot, bool white):
        dot(dot),
        white(white)
{
        QString path = "images/pieces/fantasy";

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

void Square::render(QPainter* painter, const QRectF& rect)
{
        if (white) {
                painter->setBrush(Qt::white);
        } else {
                painter->setBrush(Qt::darkGreen);
        }

        painter->fillRect(rect, painter->brush());

        if (piece_icon.isValid() and show) {
                piece_icon.render(painter, rect);
        }

        if (dot) {
                painter->setBrush(Qt::blue);
                painter->drawEllipse(QPoint(rect.x() + rect.width()/2, rect.y() + rect.height()/2), 7, 7);
        }
}

void Square::set_dot(bool d)
{
        dot = d;
}

bool Square::get_dot()
{
        return dot;
}

void Square::set_show_piece(bool show)
{
        this->show = show;
}
