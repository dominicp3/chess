#include "dialog.h"
#include "boardmodel.h"
#include <QTableView>
#include <QApplication>

int main(int argc, char* argv[])
{
        QApplication a(argc, argv);

        QPalette pal = a.palette();
        pal.setColor(QPalette::Window, Qt::black);
        a.setPalette(pal);

        Dialog w;
        w.show();

        return a.exec();
}
