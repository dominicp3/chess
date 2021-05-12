#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QHeaderView>
#include "mydelegate.h"
#include "boardmodel.h"

class MyTableView : public QTableView
{
        Q_OBJECT
public:
        explicit MyTableView(QWidget* parent = nullptr, BoardModel* boardmodel = nullptr);
};

#endif // MYTABLEVIEW_H
