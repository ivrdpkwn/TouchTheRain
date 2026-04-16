#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rain.h"
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 去边框
    setWindowFlags(windowFlags()| Qt::FramelessWindowHint);

    // 设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground);

    // 窗口最大化
    showMaximized();

    for(int i = 0; i < 200;++i){
        Rain* rain = new Rain(this);  // 指定父窗口，内嵌
        QTimer::singleShot(0, this, [=]() {
            rain->move(
                QRandomGenerator::global()->bounded(this->width()),
                QRandomGenerator::global()->bounded(this->height()));
        });
        rain->show();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
