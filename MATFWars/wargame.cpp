#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame),
    m_chatClient(new Client(this)),  // create the chat client
    m_chatModel(new QStandardItemModel(this)) // create the model to hold the messages
{
    ui->setupUi(this);

    m_chatModel->insertColumn(0);
    // set the model as the data source vor the list view
    ui->chat_listView->setModel(m_chatModel);
    // connect the signals from the chat client to the slots in this ui

    //connect(m_chatClient, &Client::connected, this, &WarGame::connectedToServer);
    connect(m_chatClient, &Client::messageReceived, this, &WarGame::messageReceived);
    connect(m_chatClient, &Client::disconnected, this, &WarGame::disconnectedFromServer);
    //connect(m_chatClient, &Client::error, this, &WarGame::error);
    connect(m_chatClient, &Client::userLeft, this, &WarGame::userLeft);
    // connect the connect button to a slot that will attempt the connection

    //connect(ui->connectButton, &QPushButton::clicked, this, &WarGame::attemptConnection);

    // connect the click of the "send" button and the press of the enter while typing to the slot that sends the message
    connect(ui->chat_lineEdit, &QLineEdit::returnPressed, this, &WarGame::sendMessage);
}

WarGame::~WarGame()
{
    delete ui;

}

PlayerWar WarGame::player1() const
{
    return m_player1;
}

PlayerWar WarGame::player2() const
{
    return m_player2;
}

Obstacle WarGame::getObstacle(size_t index) const
{
    return m_obstacles.at(index);
}

QVector<Obstacle> WarGame::generateObstacles(int x, int y)
{
    int numOfObstacles = QRandomGenerator::global()->bounded(8);

    QVector<Obstacle> obstacleArray(numOfObstacles);

    for(Obstacle &obstacle : obstacleArray){

        obstacle.setCenter(randomPoint(x, y, 2.0));
        float newDiameter = obstacle.generateDiameter(numOfObstacles);
        obstacle.setDiameter(newDiameter);

    }

    return obstacleArray;
}

PlayerWar WarGame::generatePlayer(int x, int y)
{
    PlayerWar player;
    player.setCoordinates(randomPoint(x, y, 1.0));
    return player;
}

QPointF WarGame::randomPoint(int x, int y, float playerOrObstacle)
{
    //if generatePlayer is the caller function, then playerOrObstacle = 1.0, else  playerOrObstacle = 2.0
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = (-x) + xCoord * playerOrObstacle*x;
    float yCoord = QRandomGenerator::global()->generateDouble();
    yCoord = (-y) + yCoord * 2.0*y;

    QPointF pointF(xCoord, yCoord);

    return pointF;

}

void WarGame::on_back_war_button_clicked()
{
    emit backWarClicked();
    this->hide();
}

void WarGame::messageReceived(const QString &sender, const QString &text)
{

    int newRow = m_chatModel->rowCount();

    if (m_lastUserName != sender) {

        m_lastUserName = sender;

        QFont boldFont;
        boldFont.setBold(true);

        m_chatModel->insertRows(newRow, 2);

        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + ':');

        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);

        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
    } else {
        m_chatModel->insertRow(newRow);
    }
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->chat_listView->scrollToBottom();
}

void WarGame::sendMessage()
{
    // we use the client to send the message that the user typed
    m_chatClient->sendMessage(ui->chat_lineEdit->text());
    // now we add the message to the list
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    m_chatModel->insertRow(newRow);
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), ui->chat_lineEdit->text());
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    ui->chat_lineEdit->clear();
    // scroll the view to display the new message
    ui->chat_listView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void WarGame::disconnectedFromServer()
{

    // if the client loses connection to the server
    // communicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // disable the ui to send and display messages
    ui->chat_lineEdit->setEnabled(false);
    ui->chat_listView->setEnabled(false);
    // reset the last printed username
    m_lastUserName.clear();
}

void WarGame::userLeft(const QString &username)
{

    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to communicate a user left
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    // scroll the view to display the new message
    ui->chat_listView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}



