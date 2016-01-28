#include "tcpserver.h"
#include "ui_tcpserver.h"

#include<QByteArray>

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    srv = new QTcpServer(this);
    if (!srv->listen(QHostAddress::Any, qint16(1337)))
    {
        qDebug() << "Error - Not listening\n";
    }
    else
    {
        qDebug() << "Tcp Server started successfully\n";
    }
    connect(srv, SIGNAL(newConnection()), this, SLOT(someNewConnection()));
}

TcpServer::~TcpServer()
{
    delete ui;
    qDebug() << "closing";
    srv->close();
}

void TcpServer::someNewConnection()
{
    if (srv->hasPendingConnections())
    {
        newSocket = srv->nextPendingConnection();
        qDebug() << "new socket established connection";
    }
    else
    {
        qDebug() << "Error - no pending connections!";
    }
    connect(newSocket, SIGNAL(readyRead()), this, SLOT(dataAvalaible()), Qt::UniqueConnection);
}

void TcpServer::dataAvalaible()
{
    //newSocket->waitForReadyRead(3000);
    qint64 size = newSocket->bytesAvailable();
    qDebug() << size;
    if (size <=0 || size >=60000)
    {
        qDebug() << QString("Bad size == " + size);
    }
    QByteArray arr = newSocket->read(size);
    QString receivedData = QString(arr);
    qDebug() << "receivedData: " << receivedData;

    newSocket->write("received data: ");
    newSocket->write(arr);
    newSocket->write("\n\r");
    //newSocket->flush();
}
