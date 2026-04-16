#ifndef RAIN_H
#define RAIN_H

#include <QWidget>

class Rain : public QWidget
{
    Q_OBJECT
public:
    explicit Rain(QWidget *parent = nullptr);
    void fall(int min, int max);

signals:

protected:
    void paintEvent(QPaintEvent* ev);  // 画图事件
    void timerEvent(QTimerEvent* ev);  // 定时
    void mousePressEvent(QMouseEvent* ev); // 点击时
    void mouseMoveEvent(QMouseEvent* ev);  // 移动鼠标
    void enterEvent(QEnterEvent* ev);  // 鼠标悬停

private:
    QPixmap m_pixmap;
    int m_index = 0;
    QPoint m_pt;

};

#endif // RAIN_H
