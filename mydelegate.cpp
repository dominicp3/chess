#include "mydelegate.h"
#include <iostream>

using namespace std;

MyDelegate::MyDelegate(QObject *parent) : QAbstractItemDelegate(parent)
{

}

void MyDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
        index.data().value<Square*>()->render(painter, option.rect);
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
        return QSize(60, 60);
}
