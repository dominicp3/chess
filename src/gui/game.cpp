#include "gui/game.h"

using namespace std;

Game::Game(QWidget* parent, GameState gamestate):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        boardframe(new BoardFrame(this, gamestate)),
        indicatorframe(new IndicatorFrame(this, not gamestate.white_to_move))
{
        connect(boardframe->get_tableview()->model(), SIGNAL(player_change()), indicatorframe, SLOT(switch_player()));

        int window_size = QGuiApplication::primaryScreen()->availableGeometry().width() / 3.5;
        setFixedSize(window_size, window_size);

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);
        hboxlayout->addWidget(boardframe);
        hboxlayout->addWidget(indicatorframe);

        setMinimumSize(window_size, window_size);

        setLayout(hboxlayout);
        show();
}
