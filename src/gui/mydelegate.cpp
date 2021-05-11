#include "gui/mydelegate.h"

using namespace std;

MyDelegate::MyDelegate(QObject *parent):
        QAbstractItemDelegate(parent) {}

void MyDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
        index.data().value<PieceIcon*>()->render(painter, option.rect);
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(60, 60);
}
