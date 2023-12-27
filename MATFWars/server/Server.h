#ifndef SERVER_H
#define SERVER_H

#include "../Client.h"
#include <QJsonDocument>
#include <QJsonObject>

#include <QObject>

class Server : public QTcpServer
{
    Q_OBJECT

public:

    explicit Server(QObject *parent = nullptr);
    ~Server();

    QList<QTcpSocket *> getClients();

    QTcpServer *m_server = nullptr;
    bool gameInSession = false;

signals:

    void smbConnected();
    void newMessage(QString msg);
    void smbDisconnected();
    void allPlayersConnected();

public slots:

    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);

    QString connectClicked();
    void smbConnectedToServer();
   // void forwardSetUpData(QString setUpDataString);

private:

    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> m_clients = nullptr;

};


#endif // SERVER_H
