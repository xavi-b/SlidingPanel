#include "slidingpanel.h"

namespace XB
{

void SlidingPanel::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
        event->accept();
        this->slideUp();
        return;
    }
    QFrame::keyPressEvent(event);
}

void SlidingPanel::mousePressEvent(QMouseEvent* event)
{
    if (!rect().contains(event->pos()))
    {
        event->accept();
        this->slideUp();
        return;
    }
    QFrame::mousePressEvent(event);
}

SlidingPanel::SlidingPanel(int width, QWidget* parent) : QFrame(parent)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setBlurRadius(10);
    effect->setColor(Qt::gray);
    this->setGraphicsEffect(effect);

    this->setAutoFillBackground(true);
    this->setFixedWidth(width);
    this->setMinimumHeight(100);
    this->setWindowFlags(Qt::Popup | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    this->hide();
}

void SlidingPanel::setDuration(int duration)
{
    this->duration = duration;
}

void SlidingPanel::setEasingCurve(QEasingCurve const& easingCurve)
{
    this->easingCurve = easingCurve;
}

void SlidingPanel::slideDown(int width)
{
    this->setFixedWidth(width);
    this->slideDown();
}

void SlidingPanel::slideDown()
{
    if(this->isVisible())
        return;

    if(this->parentWidget())
    {
        int x = (this->parentWidget()->width() - this->width()) / 2;
        int y = -this->height();
        int w = this->width();
        int h = this->height();
        this->setGeometry(x, y, w, h);
    }
    else
    {
        QScreen* screen = QApplication::primaryScreen();
        int x = (screen->size().width() - this->width()) / 2;
        int y = -this->height();
        int w = this->width();
        int h = this->height();
        this->setGeometry(x, y, w, h);
    }

    this->show();
    this->raise();
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(this->duration);
    animation->setEasingCurve(this->easingCurve);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->geometry().x(), 0, this->geometry().width(), this->geometry().height()));

    animation->start();
}

void SlidingPanel::slideUp()
{
    if(!this->isVisible())
        return;

    this->setVisible(true);
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(this->duration);
    animation->setEasingCurve(this->easingCurve);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(
                               this->geometry().x(),
                               -this->geometry().height(),
                               this->geometry().width(),
                               this->geometry().height()
                               ));

    connect(animation, &QPropertyAnimation::finished, this, &QWidget::hide);
    animation->start();
}

}
