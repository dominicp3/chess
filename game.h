#ifndef GAME_H
#define GAME_H

#include "gamestate.h"
#include "piecemove.h"
#include "engine.h"
#include <algorithm>
#include <QPainter>
#include <limits>
#include <memory>
#include <QDir>

class Game
{
public:
        void render(QPainter& paint);

        void select_square(int x, int y);
        bool is_white(char piece);



private:
        void render_pieces(QPainter& paint);
        void render_board(QPainter& paint);
        void render_player_indicator(QPainter& paint);
        void render_move_circles(QPainter& paint);

        GameState m_gamestate;
        PieceMove m_piecemove;
        Engine m_engine;

        // currently selected square (mouse input)
        int m_x;
        int m_y;

        std::vector<std::unique_ptr<GameState>> m_potential_states;

        QPixmap m_white_pawn_icon   = QPixmap(QDir::currentPath().append("/images/pawn_white.png"));
        QPixmap m_white_knight_icon = QPixmap(QDir::currentPath().append("/images/knight_white.png"));
        QPixmap m_white_bishop_icon = QPixmap(QDir::currentPath().append("/images/bishop_white.png"));
        QPixmap m_white_rook_icon   = QPixmap(QDir::currentPath().append("/images/rook_white.png"));
        QPixmap m_white_queen_icon  = QPixmap(QDir::currentPath().append("/images/queen_white.png"));
        QPixmap m_white_king_icon   = QPixmap(QDir::currentPath().append("/images/king_white.png"));

        QPixmap m_black_pawn_icon   = QPixmap(QDir::currentPath().append("/images/pawn_black.png"));
        QPixmap m_black_knight_icon = QPixmap(QDir::currentPath().append("/images/knight_black.png"));
        QPixmap m_black_bishop_icon = QPixmap(QDir::currentPath().append("/images/bishop_black.png"));
        QPixmap m_black_rook_icon   = QPixmap(QDir::currentPath().append("/images/rook_black.png"));
        QPixmap m_black_queen_icon  = QPixmap(QDir::currentPath().append("/images/queen_black.png"));
        QPixmap m_black_king_icon   = QPixmap(QDir::currentPath().append("/images/king_black.png"));
};
#endif // GAME_H
