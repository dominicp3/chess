#pragma once

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>
#include <QDir>
#include "board.h"
#include "game.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
        Q_OBJECT

public:
        explicit Dialog(QWidget *parent = nullptr);
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
