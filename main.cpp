#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        QPalette pal = a.palette();
        pal.setColor(QPalette::Window, Qt::black);
        a.setPalette(pal);
        Dialog w;
        w.setWindowTitle("Chess");
        w.show();
        return a.exec();
}
