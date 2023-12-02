#ifndef SERVER_H
#define SERVER_H

#include "ServerWorker.h"

class Server : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    explicit Server(QObject* parent = nullptr, quint16 port = 1234 );
    ~Server();
protected:
   // void incomingConnection(qintptr socketDescriptor) override;
/*
public slots:
    void connection();
    void communication();
*/
signals:
    void logMessage(const QString &msg);
public slots:
    void stopServer();
    void connection();
//    void clientDisconnected();

private slots:
    void broadcast(const QJsonObject &message);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
//    void userError(Client *sender);

private:
//    void jsonFromLoggedOut(Client *sender, const QJsonObject &doc);
//    void jsonFromLoggedIn(Client *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);

    ServerWorker*  m_client1;
    ServerWorker*  m_client2;
    QTcpServer* m_server;

};


#endif // SERVER_H
