#include "gui/game.h"

int main(int argc, char* argv[])
{
        QApplication a(argc, argv);

        QPalette pal = a.palette();
        pal.setColor(QPalette::Window, Qt::black);
        a.setPalette(pal);

        GameState board;
        Game game(nullptr, board);

        return a.exec();
}
