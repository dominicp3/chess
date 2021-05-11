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
#include "boardframe.h"

class Dialog : public QDialog
{
        Q_OBJECT

public:
        explicit Dialog(QWidget *parent = nullptr);

private:
        QHBoxLayout* hboxlayout;
        BoardFrame* boardwidget;
        Indicator* player_indicator;
};
#endif // DIALOG_H
