#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>


namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

private:
    Ui::TcpServer *ui;
    QTcpServer *srv;
    QTcpSocket *newSocket;

private slots:
     void someNewConnection();
     void dataAvalaible();

};

#endif // TCPSERVER_H
