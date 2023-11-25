#include "Server.h"

Server::Server(QObject *parent)
    : QObject(parent)
{
    m_server = new QTcpServer(this);
    m_client1 = nullptr;
    m_client2 = nullptr;

    connect(m_server, &QTcpServer::newConnection, this, &Server::connection);

    m_server->listen(QHostAddress::AnyIPv4, 12345);
}

Server::~Server() {
    delete m_server;
}

void Server::connection() {

    QTcpSocket* socket = m_server->nextPendingConnection();

    if(socket) {
        if(m_client1 == nullptr) {
            m_client1 = socket;
            m_client1->write("Client1");

        }
        else {
            m_client2 = socket;
            m_client2->write("Client2");
            m_client1->write("Both clients connected!");
        }

        connect(socket, &QTcpSocket::readyRead, this, &Server::communication);
        connect(socket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);
    }

    socket->flush();
    socket->waitForBytesWritten();
}

void Server::communication() {
    QTcpSocket* socketSender = dynamic_cast<QTcpSocket*>(sender());
    if(socketSender == m_client1 && m_client2 != nullptr)
        m_client2->write(socketSender->readAll());
    else
        m_client1->write(socketSender->readAll());
}

void Server::clientDisconnected() {
    m_client1 = nullptr;
    m_client2 = nullptr;
}


