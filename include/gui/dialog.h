#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QScreen>
#include <QApplication>
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
        IndicatorFrame* indicatorframe;
};
#endif // DIALOG_H
