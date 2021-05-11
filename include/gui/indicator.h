#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QPainter>

static constexpr int BORDER = 22;

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
