#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject* parent = nullptr);
    ~Server();

public slots:
    void connection();
    void communication();
    void clientDisconnected();

private:
    QTcpServer* m_server;
    QTcpSocket* m_client1;
    QTcpSocket* m_client2;
};


#endif // SERVER_H
