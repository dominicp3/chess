#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QScreen>
#include <QApplication>
#include "indicatorframe.h"
#include "boardframe.h"
#include "game/gamestate.h"

class Game : public QDialog
{
        Q_OBJECT

public:
        explicit Game(QWidget *parent, GameState gamestate);

private:
        QHBoxLayout* hboxlayout;
        BoardFrame* boardframe;
        IndicatorFrame* indicatorframe;
};
#endif // DIALOG_H
