#include "gui/dialog.h"

using namespace std;

Dialog::Dialog(QWidget* parent):
        QDialog(parent),
        hboxlayout(new QHBoxLayout(this)),
        boardframe(new BoardFrame(this)),
        indicatorframe(new IndicatorFrame(this))
{
        connect(boardframe->get_tableview()->model(), SIGNAL(player_change()), indicatorframe, SLOT(switch_player()));

        int window_size = QGuiApplication::primaryScreen()->availableGeometry().width() / 3.5;
        resize(window_size, window_size);

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);
        hboxlayout->addWidget(boardframe);
        hboxlayout->addWidget(indicatorframe);

        setMinimumSize(window_size, window_size);

        setLayout(hboxlayout);
        show();
}
