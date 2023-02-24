#include "mythread.h"
#include <QDebug>
#include "camera_gpio.h"


MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run()
{
    camera_gpio* use_gpio = new camera_gpio;
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();
    use_gpio->gpio_start();
//    qDebug() << gpio_value;

//    MainWindow* mw = new MainWindow();
//    mw->BinarzationStack();
}
