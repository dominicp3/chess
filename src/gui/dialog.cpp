#include "gui/dialog.h"

using namespace std;

Dialog::Dialog(QWidget* parent):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        boardwidget(new BoardFrame(this)),
        player_indicator(new Indicator(this))
{
        connect(boardwidget->get_boardmodel(), SIGNAL(player_change()), player_indicator, SLOT(switch_player()));
        QScreen* screen = QGuiApplication::primaryScreen();
        QRect mm = screen->availableGeometry() ;
        int size = mm.width() / 3.5;

        resize(size, size);

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);
        hboxlayout->addWidget(boardwidget);
        hboxlayout->addWidget(player_indicator);

        setMinimumSize(size, size);

        setLayout(hboxlayout);
        show();
}
