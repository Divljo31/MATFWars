#include "Server.h"

Server::Server(QObject *parent, quint16 port)
    : QTcpServer(parent)
{
    m_server = new QTcpServer(this);
    m_client1 = new ServerWorker(QTcpServer::parent());
    m_client2 = new ServerWorker(QTcpServer::parent());

    connect(m_server, &QTcpServer::newConnection, this, &Server::connection);

    m_server->listen(QHostAddress::AnyIPv4, port);
}

Server::~Server() {

    delete m_server;

}

void Server::connection() {

    QTcpSocket* socket = m_server->nextPendingConnection();



    if(socket) {

        ServerWorker* worker = new ServerWorker(QTcpServer::parent());
        worker->setServerSocket(socket);

        if(m_client1 == nullptr) {
            m_client1 = worker;
            emit logMessage(QStringLiteral("Client 1 connected"));
        }
        else {
            m_client2 = worker;
            emit logMessage(QStringLiteral("Client 2 connected"));

        }

        connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
//        connect(worker, &Client::error, this, std::bind(&Server::userError, this, worker));
        connect(worker, &ServerWorker::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
        connect(worker, &ServerWorker::logMessage, this, &Server::logMessage);

        socket->flush();
        socket->waitForBytesWritten();
    }


}

//void Server::communication() {
//    QTcpSocket* socketSender = dynamic_cast<QTcpSocket*>(sender());
//    if(socketSender == m_client1 && m_client2 != nullptr)
//        m_client2->write(socketSender->readAll());
//    else
//        m_client1->write(socketSender->readAll());
//}

//void Server::clientDisconnected() {
//    this->m_client1 = nullptr;
//    this->m_client2 = nullptr;
//}


void Server::stopServer()
{

    this->close();

    this->m_client1->disconnectFromClient();
    this->m_client2->disconnectFromClient();
}

void Server::broadcast(const QJsonObject &message)
{
    sendJson(m_client1, message);
    sendJson(m_client2, message);
}

void Server::jsonReceived(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);

}

void Server::userDisconnected(ServerWorker *sender) {
    sender->setServerSocket(nullptr);

}


void Server::sendJson(ServerWorker *destination, const QJsonObject &message)
{

    if (destination->serverSocket()->state() == QAbstractSocket::ConnectedState) {
        QDataStream clientStream(destination->serverSocket());
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}
