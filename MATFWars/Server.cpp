#include "Server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    /*m_server = new QTcpServer(this);
    m_client1 = nullptr;
    m_client2 = nullptr;

    connect(m_server, &QTcpServer::newConnection, this, &Server::connection);

    m_server->listen(QHostAddress::AnyIPv4, 12345);*/
}

Server::~Server() {
}


void Server::incomingConnection(qintptr socketDescriptor)
{

    Client *worker = new Client(QTcpServer::parent());

    if (!worker->setSocketDescriptor(socketDescriptor)) {
        worker->deleteLater();
        return;
    }

    connect(worker, &Client::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
    connect(worker, &Client::error, this, std::bind(&Server::userError, this, worker));
    connect(worker, &Client::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &Client::logMessage, this, &Server::logMessage);

    m_clients.append(worker);

    emit logMessage(QStringLiteral("New client Connected"));
}

/*
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
*/

void Server::stopServer()
{

}

void Server::broadcast(const QJsonObject &message, Client *exclude)
{
    // iterate over all the workers that interact with the clients
    for (Client *worker : m_clients) {
        if (worker == exclude)
            continue; // skip the worker that should be excluded
        sendJson(worker, message); //send the message to the worker
    }
}

void Server::jsonReceived(Client *destination, const QJsonObject &message)
{
    Q_ASSERT(destination); // make sure destination is not null
    destination->sendJson(message); // call directly the worker method

}

void Server::userDisconnected(Client *sender)
{

}

void Server::userError(Client *sender)
{

}

void Server::sendJson(Client *destination, const QJsonObject &message)
{

}
