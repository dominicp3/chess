#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QScreen>
#include <QApplication>
#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>
#include "indicatorframe.h"
#include "mydelegate.h"
#include "boardmodel.h"
#include "game/gamestate.h"

class Game : public QDialog
{
        Q_OBJECT

public:
        explicit Game(QWidget *parent, GameState gamestate);

private:
        void set_window_size();
        void set_background_colour(int r, int g, int b);
        void set_layout(GameState& gamestate);
        QTableView* new_tableview(BoardModel* boardmodel);

        IndicatorFrame* indicatorframe;
};
#endif // DIALOG_H
