#ifndef SLIDINGPANEL_H
#define SLIDINGPANEL_H

#include <QFrame>
#include <QPropertyAnimation>
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

namespace XB
{

class SlidingPanel : public QFrame
{
    Q_OBJECT
private:
    int duration = 1000;
    QEasingCurve easingCurve = QEasingCurve::OutQuad;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

public:
    SlidingPanel(int width, QWidget* parent = nullptr);

    void setDuration(int duration);
    void setEasingCurve(QEasingCurve const& easingCurve);
    void slideDown(int width);
    void slideDown();
    void slideUp();
};

}

#endif // SLIDINGPANEL_H
