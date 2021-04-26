#include "piece.h"

Piece::Piece(char type, char colour, int x, int y):
        m_type(type),
        m_colour(colour),
        m_x(x),
        m_y(y) {}

void Piece::set_position(int x, int y)
{
        m_x = x;
        m_y = y;
}

int Piece::x()
{
        return m_x;
}

int Piece::y()
{
        return m_y;
}

void Piece::render(QPainter &paint)
{
        paint.drawPixmap(70 * m_x + 37, 626 - (69 * m_y + 103), m_icon);
}
