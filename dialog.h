#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <QDrag>
#include <QVariant>
#include "mydelegate.h"
#include "mytableview.h"
#include "boardmodel.h"
#include "indicator.h"

class Dialog : public QDialog
{
        Q_OBJECT

public:
        Dialog(QWidget *parent = nullptr);

        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;

private:
        QPoint startpos;

        QHBoxLayout* hboxlayout;
        BoardModel* boardmodel;
        MyTableView* tableview;
        Indicator* player_indicator;
};
#endif // DIALOG_H
