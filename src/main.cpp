#include "gui/game.h"

int main(int argc, char* argv[])
{
        QApplication a(argc, argv);

        GameState board;
        Game game(nullptr, board);

        return a.exec();
}
