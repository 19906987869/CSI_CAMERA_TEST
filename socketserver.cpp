#include "socketserver.h"
#include <QDebug>
#include "mainwindow.h"

socketserver::socketserver(QObject *parent) : QObject(parent)
{
    qtcpServer = NULL;
    qtcpSocket = NULL;
    //监听套字节，指定父对象，让其自动回收空间
    qtcpServer = new QTcpServer(this);
    //qtcpSocket = new QTcpSocket(this);
    qtcpServer->listen(QHostAddress::Any,8886);
    //setWindowTitle("服务器：8886");
    connect(qtcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的套接字
        qtcpSocket = qtcpServer->nextPendingConnection();
        //获取对方的IP和端口
        QString ip = qtcpSocket->peerAddress().toString();
        qint16 port = qtcpSocket->peerPort();
        QString temp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
        //ui->textEditRead->setText(temp);
        //必须放在里面，因为建立好链接才能读，或者说tcpSocket有指向才能操作
        connect(qtcpSocket, &QTcpSocket::readyRead,
                [=]()
                {
                    //从通信套接字中取出内容
                    QByteArray array = qtcpSocket->readAll();
                    //ui->textEditRead->append(array);
                    qDebug() << array;
                }
          );
    });
}


void socketserver::Send(QString sum)
{
    if(NULL == qtcpSocket)
    {
        return;
    }
    //给对方发送数据， 使用套接字是tcpSocket
    qtcpSocket->write(sum.toUtf8().data());
}

void socketserver::Close()
{
    if(NULL == qtcpSocket)
    {
        return;
    }
    //主动和客户端断开连接
    qtcpSocket->disconnectFromHost();
    qtcpSocket->close();
    qtcpSocket = NULL;

}
