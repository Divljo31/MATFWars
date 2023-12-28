#include "Server.h"

Server::Server(QObject *parent) : m_nNextBlockSize(0)
{

    m_server = new QTcpServer();

    connect(this, &QTcpServer::newConnection, this, &Server::smbConnectedToServer);
}

Server::~Server()
{
    delete m_server;

}

QList<QTcpSocket *> Server::getClients()
{

    return m_clients;
}

void Server::newConnection()
{

    QTcpSocket *clientSocket = m_server->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::gotDisconnection);

    m_clients << clientSocket;

    for (QTcpSocket *client : m_clients)
    {
        if(m_clients.size() == 1){
            sendToClient(client, "Player 1 has connected!");
            sendToClient(client, "Waiting for the other player...");
        }
        else{
            sendToClient(client, "Player 2 has connected!");
        }
    }
}


void Server::readClient()
{

    QTcpSocket *clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);


    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        QString str;
        in >> str;

        emit newMessage(str);

        m_nNextBlockSize = 0;


        for (QTcpSocket *client : m_clients)
        {
            if (sendToClient(client, str) == -1)
            {
                qDebug() << "Some error occured";
            }
        }
    }
}


void Server::gotDisconnection()
{

    m_clients.removeAt(m_clients.indexOf((QTcpSocket*)sender()));
    for (QTcpSocket *client : m_clients)
    {
        if (sendToClient(client, "Somebody has disconnected!") == -1)
        {
            qDebug() << "Some error occured";
        }
    }

    emit smbDisconnected();

}

qint64 Server::sendToClient(QTcpSocket *socket, const QString &str)
{

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}

void Server::smbConnectedToServer()
{

    emit smbConnected();
}

