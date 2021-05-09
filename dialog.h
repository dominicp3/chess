#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHeaderView>
#include <QHBoxLayout>
#include "gamestate.h"
#include "piecemove.h"
#include "mydelegate.h"
#include "boardmodel.h"

class Dialog : public QDialog
{
        Q_OBJECT

public:
        Dialog(QWidget *parent = nullptr);

private slots:
        void cell_click(const QModelIndex& index);

private:
        QHBoxLayout* hboxlayout;
        QTableView* tableview;
        BoardModel* boardmodel;
};
#endif // DIALOG_H
