#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QPainter>

static constexpr int BORDER = 22;

class IndicatorFrame : public QWidget
{
        Q_OBJECT
public:
        explicit IndicatorFrame(QWidget *parent = nullptr, bool top = false);

protected:
        void paintEvent(QPaintEvent* event) override;

public slots:
        void switch_player();

private:
        bool top;

};

#endif // INDICATOR_H
