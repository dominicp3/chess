#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QDragEnterEvent>
#include <QHeaderView>
#include "mydelegate.h"
#include "boardmodel.h"

class MyTableView : public QTableView
{
public:
        explicit MyTableView(QWidget* parent = nullptr, BoardModel* boardmodel = nullptr);

        void dragEnterEvent(QDragEnterEvent* event) override;
        void dragMoveEvent(QDragMoveEvent* event) override;
        void dragLeaveEvent(QDragLeaveEvent* event) override;
        void dropEvent(QDropEvent* event) override;

        QPoint pos;
};

#endif // MYTABLEVIEW_H
