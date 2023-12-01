#include "Client.h"

Client::Client(QObject *parent)
    : QObject(parent)
    , m_serverSocket(new QTcpSocket(this))
{
    connect(m_serverSocket, &QTcpSocket::readyRead, this, &Client::receiveJson);
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &Client::disconnectedFromClient);
    connect(m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &Client::error);
}

bool Client::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}
void Client::disconnectFromClient()
{
    m_serverSocket->disconnectFromHost();
}

QString Client::userName() const
{
    return m_userName;
}

void Client::setUserName(const QString &userName)
{
    m_userName = userName;
}

void Client::receiveJson()
{

    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);

    socketStream.setVersion(QDataStream::Qt_5_7);

    for (;;) {

        socketStream.startTransaction();

        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {

            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    emit jsonReceived(jsonDoc.object());
                else
                    emit logMessage("Invalid message: " + QString::fromUtf8(jsonData));
            } else {
                emit logMessage("Invalid message: " + QString::fromUtf8(jsonData));
            }
        } else {
            break;
        }
    }
}

void Client::sendJson(const QJsonObject &json)
{

    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

    emit logMessage("Sending to " + userName() + " - " + QString::fromUtf8(jsonData));

    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_7);
    socketStream << jsonData;
}
