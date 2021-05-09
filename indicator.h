#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QPainter>

class Indicator : public QWidget
{
        Q_OBJECT
public:
        explicit Indicator(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent* event) override;

public slots:
        void switch_player();

private:
        bool top = false;

};

#endif // INDICATOR_H
