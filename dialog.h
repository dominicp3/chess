#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>
#include <QTableView>
#include <QDir>
#include <utility>
#include <QLabel>
#include <QSizePolicy>
#include <QPalette>
#include <QSvgRenderer>
#include <QSvgWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QBoxLayout>
#include "gamestate.h"
#include "piecemove.h"
#include "grid.h"
#include "mydelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
        Q_OBJECT

public:
        Dialog(QWidget *parent = nullptr);
        ~Dialog();

//        void paintEvent(QPaintEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

private slots:
        void nextFrame();

private:
        Ui::Dialog *ui;
        QTimer *timer = nullptr;

        void add_circles();

//      FUNCTIONS FROM GAME.H
        void render(QPainter& paint);

        void select_square(int x, int y);
        bool is_white(char piece);

        GameState m_gamestate;

        // currently selected square (mouse input)
        int m_x;
        int m_y;

        std::vector<std::unique_ptr<GameState>> m_potential_states;

        QTableView* table = new QTableView(this);
        Grid* grid = new Grid(table, m_gamestate);
};
#endif // DIALOG_H
