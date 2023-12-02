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

public:
    explicit Client(QObject *parent = nullptr);

    QTcpSocket *clientSocket() const;
    void setClientSocket(QTcpSocket *newClientSocket);

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void sendMessage(const QString &text);
    void disconnectFromHost();

private slots:
    void onReadyRead();

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void userJoined(const QString &username);
    void userLeft(const QString &username);

private:
    QTcpSocket *m_clientSocket;
    void jsonReceived(const QJsonObject &doc);

};

#endif // CLIENT_H
