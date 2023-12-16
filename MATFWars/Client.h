#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTimer>


class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool currentStatus READ getStatus NOTIFY statusChanged)


public:
    explicit Client(QObject *parent, const QString hostAddress, quint16 portNumber);
    bool getStatus();


    QTcpSocket *m_socket;

    QString host() const;
    void setHost(const QString &newHost);
    quint16 port() const;
    void setPort(quint16 newPort);

    QString name() const;
    void setName(const QString &newName);

public slots:
    void closeConnection();
    void connect2host();

    void setStatus(bool newStatus);
    void receivedSomething(QString msg);
    void gotError(QAbstractSocket::SocketError err);
    void sendClicked(QString msg);
    void connectClicked();
    void disconnectClicked();

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

signals:

    void statusChanged(bool status);
    void someError(QString err);
    void someMessage(QString msg);

    void hasReadSome(QString msg);


private:

    QString m_name;
    QString m_host;
    quint16 m_port;
    bool m_status;
    quint16 m_NextBlockSize;
    QTimer *m_timeoutTimer;

};

#endif // CLIENT_H
