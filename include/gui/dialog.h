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
#include "indicatorframe.h"
#include "boardframe.h"

class Dialog : public QDialog
{
        Q_OBJECT

public:
        explicit Dialog(QWidget *parent = nullptr);

private:
        QHBoxLayout* hboxlayout;

        BoardFrame* boardframe;
        IndicatorFrame* player_indicator;
};
#endif // DIALOG_H
