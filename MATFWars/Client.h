#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QAbstractSocket>
#include <QJsonObject>
#include <QJsonParseError>

class Client : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Client)
public:
    explicit Client(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const;
    void setUserName(const QString &userName);
    void sendJson(const QJsonObject &jsonData);
signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
public slots:
    void disconnectFromClient();
private slots:
    void receiveJson();
private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
};

#endif // CLIENT_H
