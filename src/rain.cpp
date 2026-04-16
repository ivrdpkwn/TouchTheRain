#include "rain.h"
#include "qapplication.h"

#include <QMouseEvent>
#include <QPainter>
#include <QRandomGenerator>

Rain::Rain(QWidget *parent)
    : QWidget{parent}
{
    m_pixmap.load(":/img/rain0.png");  // 初始化界面
    setFixedSize(m_pixmap.size()/2);

    startTimer(100);

}

void Rain::fall(int min, int max)
{
    m_index++;
    if (m_index > 1) {
        m_index = 0;
    }

    QString imgPath = QString(":/img/rain%1.png").arg(m_index);
    m_pixmap.load(imgPath);
    update();

    int stepX = QRandomGenerator::global()->bounded(min, max);
    int stepY = QRandomGenerator::global()->bounded(min, max);

    int curX = this->geometry().topLeft().x();
    int curY = this->geometry().topLeft().y() + stepY;


    QScreen *screen = this->screen();
    QRect rect = screen->geometry();
    if (curX >= rect.right()) {
        curX = rect.left();
    }
    if (curY >= rect.bottom()) {
        curY = rect.top();
    }

    move(curX,curY);
}

void Rain::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter p(this);
    p.drawPixmap(rect(), m_pixmap);
}

void Rain::timerEvent(QTimerEvent *ev)
{
    Q_UNUSED(ev);
    fall(10,30);
}

void Rain::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){ // 当鼠标左击时
        m_pt = ev->globalPosition().toPoint() - this->geometry().topLeft();
        // 屏幕坐标（绝对坐标） ev->globalPosition().toPoint()
        // 控件内部坐标（相对坐标） ev->pos()
    }
}

void Rain::mouseMoveEvent(QMouseEvent *ev)
{

    if(ev->buttons() & Qt::LeftButton){ // 当鼠标左键出现时
        this->move(ev->globalPosition().toPoint() - m_pt);  // 求出左上角的位置
    }
}

void Rain::enterEvent(QEnterEvent *ev)
{
    fall(0,200);
}
