#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QObject>
class socketserver : public QObject
{
public:
    explicit socketserver(QObject *parent = nullptr);
    void connectsocket();
    void Send(QString sum);
    void Close();
    QTcpSocket *qtcpSocket;
    QTcpServer *qtcpServer;
};

#endif // SOCKETSERVER_H
