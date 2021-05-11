#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QDrag>
#include <QDragEnterEvent>
#include <QHeaderView>
#include "mydelegate.h"
#include "boardmodel.h"

class MyTableView : public QTableView
{
        Q_OBJECT
public:
        explicit MyTableView(QWidget* parent = nullptr, BoardModel* boardmodel = nullptr);

protected:
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dragMoveEvent(QDragMoveEvent* event) override;
        void dragLeaveEvent(QDragLeaveEvent* event) override;
        void dropEvent(QDropEvent* event) override;

private:
        bool outside = false;
};

#endif // MYTABLEVIEW_H
