#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHeaderView>
#include <QHBoxLayout>
#include "mydelegate.h"
#include "boardmodel.h"
#include "indicator.h"

class Dialog : public QDialog
{
        Q_OBJECT

public:
        Dialog(QWidget *parent = nullptr);

private:
        QHBoxLayout* hboxlayout;
        QTableView* tableview;
        BoardModel* boardmodel;
        Indicator* player_indicator;
};
#endif // DIALOG_H
