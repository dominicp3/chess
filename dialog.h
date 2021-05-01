#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>
#include <QDir>
#include "gamestate.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
        Q_OBJECT

public:
        Dialog(QWidget *parent = nullptr);
        ~Dialog();

        void paintEvent(QPaintEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

private slots:
        void nextFrame();

private:
        Ui::Dialog *ui;
        Game game;
        QTimer *timer = nullptr;
};
#endif // DIALOG_H
