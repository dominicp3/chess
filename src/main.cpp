#include "gui/dialog.h"

int main(int argc, char* argv[])
{
        QApplication a(argc, argv);

        QPalette pal = a.palette();
        pal.setColor(QPalette::Window, Qt::black);
        a.setPalette(pal);

        Dialog w;

        return a.exec();
}
