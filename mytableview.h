#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QHeaderView>
#include "mydelegate.h"
#include "boardmodel.h"
#include "boardmodel.h"


class MyTableView : public QTableView
{
public:
        MyTableView(QWidget* parent = nullptr, BoardModel* boardmodel = nullptr);
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dragMoveEvent(QDragMoveEvent* event) override;
        void dropEvent(QDropEvent* event) override;

private:
        QPoint startpos;
};

#endif // MYTABLEVIEW_H
