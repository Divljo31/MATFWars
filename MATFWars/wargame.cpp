#include "wargame.h"
#include "Canvas.h"
#include "Function.h"
#include "ObstacleNode.h"
#include "PlayerNode.h"
#include "qtimer.h"
#include "ui_wargame.h"
#include <cmath>

WarGame::WarGame(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame),
    m_canvas(new Canvas(this)),
    m_client(client)
{
    ui->setupUi(this);
    ptrCheck = new Check();
    ptrWinner = new Winner();


    ui->chat_textEdit->setReadOnly(true);
    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);
    connect(m_client, &Client::someMessage, this, &WarGame::clientReceivedMessage);
    connect(ui->chat_send_button, &QPushButton::clicked, this, &WarGame::sendMessage);
    connect(ui->chat_lineEdit, &QLineEdit::returnPressed, this, &WarGame::sendMessage);

    ui->fire_war_button->installEventFilter(this);
    ui->quit_war_button->installEventFilter(this);
    ui->back_war_button->installEventFilter(this);
    ui->chat_send_button->installEventFilter(this);

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);
    connect(this, &WarGame::newPlayerIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addPlayer);
    connect(this, &WarGame::newObstacleIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addObstacle);
    connect(this, &WarGame::setCoordinateSystem, dynamic_cast<Canvas *>(m_canvas), &Canvas::addCoordinateSystem);
    connect(this, &WarGame::cleanUpCanvas, dynamic_cast<Canvas *>(m_canvas), &Canvas::cleanUp);

    connect(ui->fire_war_button, &QPushButton::clicked, this, &WarGame::inputTaken);
    connect(ui->leFunctionInput, &QLineEdit::returnPressed, this, &WarGame::inputTaken);
    connect(this, &WarGame::newFunctionIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::setFunction);

    backStyle=ui->back_war_button->styleSheet();
    quitStyle=ui->quit_war_button->styleSheet();
    fireStyle=ui->fire_war_button->styleSheet();
    chatStyle=ui->chat_send_button->styleSheet();

    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);


    ui->back_war_button->setDefault(false);
    ui->back_war_button->setAutoDefault(false);
    ui->quit_war_button->setDefault(false);
    ui->quit_war_button->setAutoDefault(false);
    ui->chat_send_button->setDefault(false);
    ui->chat_send_button->setAutoDefault(false);
    ui->fire_war_button->setDefault(false);
    ui->fire_war_button->setAutoDefault(false);
    ui->leFunctionInput->setFocusPolicy(Qt::StrongFocus);
}

WarGame::~WarGame()
{
    delete ui;
    delete ptrCheck;
    //sendToClient(m_client, "destroy");
    cleanUp();
}

void WarGame::createObstacleJsonArray(QJsonArray *obstaclesJson)
{
    for (Obstacle *o : obstacles){
        QJsonObject obstacleObject = o->createJson();
        obstaclesJson->append(obstacleObject);
    }
}

void WarGame::setCanvas()
{
    m_canvas->setSceneRect(ui->gvCanvas->rect());

    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);

    emit setCoordinateSystem();
}

void WarGame::startWarGame()
{
    setCanvas();

    player0 = generatePlayer(m_client->name(), gridWidth, gridHeight);

    player1 = generatePlayer("Player 2", gridWidth, gridHeight);
    player1->flipX();

    generateObstacles(gridWidth, gridHeight);

    QJsonObject player0Json = player0->createJson();
    QJsonObject player1Json = player1->createJson();

    QJsonArray obstaclesArray;

    createObstacleJsonArray(&obstaclesArray);

    QJsonObject setUpData;
    setUpData["type"] = "setUpData";
    setUpData["player0"] = player0Json;
    setUpData["player1"] = player1Json;
    setUpData["obstacles"] = obstaclesArray;

    QJsonDocument jsonDocument(setUpData);
    QString setUpDataString = jsonDocument.toJson();
    //qDebug() << setUpDataString.toStdString();

    m_client->sendData(setUpDataString);

//    drawCanvas();
}

//void WarGame::sendSetUpData(QString setUpDataString){

//    m_client->sendMsg(setUpDataString);
//}

void WarGame::fireFunction(std::string fString)
{

    ui->leFunctionInput->setText("");
    ui->leFunctionInput->setDisabled(true);

    QPointF firePosition = getFirePosition();
    Function* function = new Function(fString, firePosition.x());

    function->translatePointsPlayerView(0, firePosition.y());

    collisionDetection(function);

    function->scaleToCanvas(m_canvas->width(), m_canvas->height(), dynamic_cast<Canvas *>(m_canvas)->gridWidth());
    function->translatePointsObserverView(m_canvas->width()/2, m_canvas->height()/2);

    QRectF sceneRect = QRectF(m_canvas->sceneRect());
    FunctionNode* node = new FunctionNode(function, sceneRect.width(), sceneRect.height());

    emit newFunctionIsSet(node);

    // ako izadjem iz igrice onda se svj uradi ovo i pomesaju se igraci, mora bolje resenje
    QTimer::singleShot(2000, [this, function]() {
        if (playerWinner != nullptr) {
            ptrWinner->setWinnerName(player0->name());
            ptrWinner->show();
            ui->leFunctionInput->setDisabled(true);
            emit cleanUpCanvas();
        }
        else {
            switchPlayer();
            if((m_fromCreate && currentPlayer == 0) || (!m_fromCreate && currentPlayer == 1)) {
                ui->leFunctionInput->setDisabled(false);
            }
        }


        //ui->leFunctionInput->setDisabled(false);
        delete function;
    });
}

QPointF WarGame::getFirePosition() {
    if (currentPlayer == 0)
        return QPointF(player0->coordinate().x() + player0->diameter()/2, player0->coordinate().y());
    else
        return QPointF(player1->coordinate().x() + player1->diameter()/2, player1->coordinate().y());
}

// TODO: ako se pogodi -> kraj partije
void WarGame::collisionDetection(Function* function) {
    int cutoff = 0;

    for (QPointF p : function->points()) {
        if (isPointInCircle(p, player0->coordinate(), player0->diameter() / 2)) {
            function->removePointsAfterCutoff(cutoff);
            playerWinner = player1;
        }

        if (isPointInCircle(p, player1->coordinate(), player1->diameter() / 2)) {
            function->removePointsAfterCutoff(cutoff);
            playerWinner = player0;
        }

        for (Obstacle* obstacle : obstacles) {
            if(isPointInCircle(p, obstacle->center(), obstacle->diameter()/2)) {

                function->removePointsAfterCutoff(cutoff);
                obstacle->gotHit();
               // qDebug() << obstacle->health();

                if (!obstacle->isAlive()) {
                    obstacles.remove(obstacle);
                    delete obstacle;
                }
                return;
            }
        }

        if (p.y() < -gridHeight/2) {
            function->removePointsAfterCutoff(cutoff);
            return;
        }

        if (p.y() > gridHeight/2) {
            function->removePointsAfterCutoff(cutoff);
            return;
        }

        cutoff++;
    }
}

bool WarGame::isPointInCircle(QPointF p, QPointF center, double radius) {
    double distance = std::sqrt(std::pow(p.x() - center.x(), 2) + std::pow(p.y() - center.y(), 2));
    return distance < radius;
}


void WarGame::generateObstacles(int width, int height)
{
    int numOfObstacles = 1 + QRandomGenerator::global()->bounded(10);
    int generatedObstacles = 0;
    while(generatedObstacles < numOfObstacles) {
        Obstacle* obstacle = new Obstacle();

        obstacle->setCenter(randomPoint(width, height, 1.0));
        double newDiameter = obstacle->generateDiameter();
        obstacle->setDiameter(newDiameter);

        if (allowedObstacle(obstacle)) {
            obstacles.insert(obstacle);
            generatedObstacles++;
        } else {
            delete obstacle;
        }
    }
}

bool WarGame::allowedObstacle(Obstacle *o)
{
    double distFrom0 = std::hypot(o->center().x() - player0->coordinate().x(), o->center().y() - player0->coordinate().y());
    double distFrom1 = std::hypot(o->center().x() - player1->coordinate().x(), o->center().y() - player1->coordinate().y());

    return distFrom0 > (o->diameter() + player0->diameter()) / 2
           && distFrom1 >  (o->diameter() + player1->diameter()) / 2;
}

Player* WarGame::generatePlayer(QString name, int width, int height)
{
    Player *player = new Player(name);

    // generise playera tkd se ne sece sa borderima
    QPointF playerPos = randomPoint(width - player->diameter(), height - 2*player->diameter(), 0.2);
    player->setCoordinates(playerPos);

    return player;
}

// x-> width, y -> height, playerOrObstacle -> procenat ekrana gde moze da se generise
QPointF WarGame::randomPoint(int width, int height, double areaPercent)
{
    //if generatePlayer is the caller function, then playerOrObstacle = 1.0, else  playerOrObstacle = 2.0
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = -width / 2 + xCoord * areaPercent * width;

    float yCoord = QRandomGenerator::global()->generateDouble();
    yCoord = -height / 2 + yCoord * height;

    QPointF pointF(xCoord, yCoord);

    return pointF;

}

void WarGame::cleanUp()
{
    emit cleanUpCanvas();

    for (Obstacle* o : obstacles) {
        delete o;
    }
    obstacles.clear();

    if (player0 != nullptr)
        delete player0;
    if (player1 != nullptr)
        delete player1;
}

void WarGame::switchPlayer()
{
    flipCanvas();
    drawCanvas();
    currentPlayer = 1 - currentPlayer;
}

void WarGame::flipCanvas() {
    player0->flipX();
    player1->flipX();

    for(Obstacle* o : obstacles) {
        o->flipX();
    }

    emit cleanUpCanvas();
}

void WarGame::drawCanvas() {

    PlayerNode *pn0 = new PlayerNode(player0);
    emit newPlayerIsSet(pn0);

    PlayerNode *pn1 = new PlayerNode(player1);
    emit newPlayerIsSet(pn1);

    for(Obstacle* o : obstacles) {
        ObstacleNode *on = new ObstacleNode(o);
        emit newObstacleIsSet(on);
    }
}

void WarGame::on_back_war_button_clicked()
{
    cleanUp();
    emit backWarClicked();
    this->hide();
}

void WarGame::clientReceivedMessage(QString msg)
{
    QByteArray jsonData = msg.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObj = doc.object();

    if (msg == "Player 2 has connected!" && m_fromCreate){
        startWarGame();
    }

    else if (jsonObj["type"] == "setUpData" && !m_fromCreate) {

        setCanvas();
//        qDebug() << jsonObj;
        QJsonObject player0Json = jsonObj.value("player0").toObject();
        player0 = new Player(player0Json["m_name"].toString());
        QJsonObject coordinates0 = player0Json.value("m_coordinate").toObject();
        double x0 = coordinates0.value("x").toDouble();
        double y0 = coordinates0.value("y").toDouble();
        player0->setCoordinates(QPointF(x0, y0));

        QJsonObject player1Json = jsonObj.value("player1").toObject();
        player1 = new Player(m_client->name());
        QJsonObject coordinates1 = player1Json.value("m_coordinate").toObject();
        double x1 = coordinates1.value("x").toDouble();
        double y1 = coordinates1.value("y").toDouble();
        player1->setCoordinates(QPointF(x1, y1));

        QJsonArray obstaclesArray = jsonObj.value("obstacles").toArray();

        for(Obstacle *o : obstacles){
            delete o;
        }

        obstacles.clear();

        // Iterating through each obstacle
        for (const QJsonValue &value : obstaclesArray) {
            QJsonObject obstacle = value.toObject();

            // Extracting obstacle data
            Obstacle *tmp = new Obstacle();
            QJsonObject center = obstacle.value("m_center").toObject();
            double centerX = center.value("x").toDouble();
            double centerY = center.value("y").toDouble();
            double diameter = obstacle.value("m_diameter").toDouble();
            int health = obstacle.value("m_health").toInt();
            int maxHealth = obstacle.value("m_maxHealth").toInt();
            tmp->setCenter(QPointF(centerX, centerY));
            tmp->setDiameter(diameter);
            tmp->setHealth(health);
            tmp->setMaxHealth(maxHealth);

            obstacles.insert(tmp);
        }


        ui->leFunctionInput->setDisabled(true);


        QJsonObject msgData;
        msgData["type"] = "name";
        msgData["data"] = m_client->name();
        QJsonDocument jsonDocument(msgData);
        QString msgString = jsonDocument.toJson();
        m_client->sendData(msgString);



        drawCanvas();
    }
    else if(jsonObj["type"] == "name" && m_fromCreate){
        player1->setName(jsonObj["data"].toString());
//        qDebug() << "\n\n\n" << player1->name();


        dynamic_cast<Canvas *>(m_canvas)->update();
        emit cleanUpCanvas();
        drawCanvas();
    }
    else if(jsonObj["type"] == "func"){
        if((m_fromCreate && currentPlayer == 1) || (!m_fromCreate && currentPlayer == 0)){
            ui->leFunctionInput->setDisabled(true);
        }

        fireFunction(jsonObj["data"].toString().toStdString());
        ui->chat_textEdit->append(tr("<font color=\"blue\"><i>") + jsonObj["player"].toString() + " played y = " + jsonObj["data"].toString() + tr("</i></font>"));
    }
    else if(jsonObj["type"] == "msg"){
        ui->chat_textEdit->append(tr("<font><b>") + jsonObj["name"].toString() + tr(": </b></font>") + jsonObj["message"].toString());
    }


//    else if(colonIndex != -1){
//        QString name = msg.left(colonIndex);
//        QString msgText = msg.right(msg.length() - colonIndex - 1);
//        ui->chat_textEdit->append(tr("<font><b>") + name + tr(": </b>")+ msgText + tr("</font>"));
//    }
//    else{
//        ui->chat_textEdit->append(msg);
//    }
}

void WarGame::setClient(Client *newClient)
{
    m_client = newClient;
}

void WarGame::sendMessage()
{
    if (m_client->getStatus()) {
        // The socket is connected, proceed with sending the message
        QString message = ui->chat_lineEdit->text();
        QJsonObject msgData;
        msgData["type"] = "msg";
        msgData["message"] = message;
        msgData["name"] = m_client->name();
        QJsonDocument jsonDocument(msgData);
        QString msgString = jsonDocument.toJson();
        m_client->sendData(msgString);
        ui->chat_lineEdit->clear();

    } else {
        // Handle the case when the socket is not connected
        qDebug() << "Socket is not connected!";
    }
}


void WarGame::on_quit_war_button_clicked()
{
    ptrCheck->show();
}

void WarGame::inputTaken()
{
    QJsonObject msgData;
    msgData["type"] = "func";
    msgData["player"] = m_client->name();
    msgData["data"] = ui->leFunctionInput->text();
    QJsonDocument jsonDocument(msgData);
    QString msgString = jsonDocument.toJson();
    m_client->sendData(msgString);
}

void WarGame::setFromCreate(bool newFromCreate)
{
    m_fromCreate = newFromCreate;
}

bool WarGame::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->fire_war_button && event->type()==QEvent::Enter){
        ui->fire_war_button->setCursor(Qt::PointingHandCursor);
        ui->fire_war_button->setStyleSheet(fireStyle+"border: 7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->quit_war_button && event->type()==QEvent::Enter){
        ui->quit_war_button->setCursor(Qt::PointingHandCursor);
        ui->quit_war_button->setStyleSheet(quitStyle+"border: 7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->back_war_button && event->type()==QEvent::Enter){
        ui->back_war_button->setCursor(Qt::PointingHandCursor);
        ui->back_war_button->setStyleSheet(backStyle+"border: 7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->chat_send_button && event->type()==QEvent::Enter){
        ui->chat_send_button->setCursor(Qt::PointingHandCursor);
        ui->chat_send_button->setStyleSheet(chatStyle+"border: 3px solid;");
    }
    else if(obj==ui->fire_war_button && event->type()==QEvent::Leave){
        ui->fire_war_button->setStyleSheet(fireStyle);
    }
    else if(obj==ui->quit_war_button && event->type()==QEvent::Leave){
        ui->quit_war_button->setStyleSheet(quitStyle);
    }
    else if(obj==ui->back_war_button && event->type()==QEvent::Leave){
        ui->back_war_button->setStyleSheet(backStyle);
    }
    else if(obj==ui->chat_send_button && event->type()==QEvent::Leave){
        ui->chat_send_button->setStyleSheet(chatStyle);
    }

    return QDialog::eventFilter(obj,event);
}
