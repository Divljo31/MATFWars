#ifndef SERVER_H
#define SERVER_H

#include "Client.h"

class Server : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    explicit Server(QObject* parent = nullptr);
    ~Server();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
/*
public slots:
    void connection();
    void communication();
    void clientDisconnected();
*/
signals:
    void logMessage(const QString &msg);
public slots:
    void stopServer();
private slots:
    void broadcast(const QJsonObject &message, Client *exclude);
    void jsonReceived(Client *sender, const QJsonObject &doc);
    void userDisconnected(Client *sender);
    void userError(Client *sender);

private:
    void jsonFromLoggedOut(Client *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(Client *sender, const QJsonObject &doc);
    void sendJson(Client *destination, const QJsonObject &message);
    QVector<Client *> m_clients;
    /*
    QTcpServer* m_server;
    QTcpSocket* m_client1;
    QTcpSocket* m_client2;
    */
};


#endif // SERVER_H
