#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QAbstractItemDelegate>
#include "pieceicon.h"

class MyDelegate : public QAbstractItemDelegate
{
public:
        explicit MyDelegate(QObject *parent = nullptr);
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // MYDELEGATE_H
