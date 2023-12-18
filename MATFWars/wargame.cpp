#include "wargame.h"
#include "Canvas.h"
#include "Function.h"
#include "ObstacleNode.h"
#include "PlayerNode.h"
#include "qtimer.h"
#include "ui_wargame.h"
#include <cmath>

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame),
    m_canvas(new Canvas(this))
{
    ui->setupUi(this);
    ptrCheck=new Check();

    //menjam
    ui->fire_war_button->installEventFilter(this);
    ui->quit_war_button->installEventFilter(this);
    ui->back_war_button->installEventFilter(this);

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);
    connect(this, &WarGame::newPlayerIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addPlayer);
    connect(this, &WarGame::newObstacleIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addObstacle);
    connect(this, &WarGame::setCoordinateSystem, dynamic_cast<Canvas *>(m_canvas), &Canvas::addCoordinateSystem);
    connect(this, &WarGame::cleanUpCanvas, dynamic_cast<Canvas *>(m_canvas), &Canvas::cleanUp);

    connect(ui->leFunctionInput, &QLineEdit::returnPressed, this, &WarGame::fireFunction);
    connect(this, &WarGame::newFunctionIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::setFunction);

    backStyle=ui->back_war_button->styleSheet();
    quitStyle=ui->quit_war_button->styleSheet();
    fireStyle=ui->fire_war_button->styleSheet();

    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);
}

WarGame::~WarGame()
{
    delete ui;
    delete ptrCheck;
    cleanUp();
}

void WarGame::startWarGame()
{
    m_canvas->setSceneRect(ui->gvCanvas->rect());

    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);

    emit setCoordinateSystem();

    player0 = generatePlayer(gridWidth, gridHeight);

    player1 = generatePlayer(gridWidth, gridHeight);
    player1->flipX();

    generateObstacles(gridWidth, gridHeight);

    drawCanvas();
}

void WarGame::fireFunction()
{
    std::string fString = ui->leFunctionInput->text().toStdString();

    QPointF firePosition = getFirePosition();
    Function* function = new Function(fString, firePosition.x());

    function->translatePointsPlayerView(0, firePosition.y());

    // TODO: ovde za proveru sudara
    collisionDetection(function);

    function->scaleToCanvas(m_canvas->width(), m_canvas->height(), dynamic_cast<Canvas *>(m_canvas)->gridWidth());
    function->translatePointsObserverView(m_canvas->width()/2, m_canvas->height()/2);

    QRectF sceneRect = QRectF(m_canvas->sceneRect());
    FunctionNode* node = new FunctionNode(function, sceneRect.width(), sceneRect.height());

    emit newFunctionIsSet(node);

    // ako izadjem iz igrice onda se svj uradi ovo i pomesaju se igraci, mora bolje resenje
    QTimer::singleShot(2000, [this]() {
        switchPlayer();
    });
}

QPointF WarGame::getFirePosition() {
    if (currentPlayer == 0)
        return QPointF(player0->coordinate().x() + player0->diameter()/2, player0->coordinate().y());
    else
        return QPointF(player1->coordinate().x() + player1->diameter()/2, player1->coordinate().y());
}

void WarGame::collisionDetection(Function *f) {
    int cutoff = 0;

    for (QPointF p : f->points()) {
        if (isPointInCircle(p, player0->coordinate(), player0->diameter() / 2)) {
            f->removePointsAfterCutoff(cutoff);
            return;
        }

        if (isPointInCircle(p, player1->coordinate(), player1->diameter() / 2)) {
            f->removePointsAfterCutoff(cutoff);
            return;
        }

        for (Obstacle* obstacle : obstacles) {
            if(isPointInCircle(p, obstacle->center(), obstacle->diameter()/2)){
                f->removePointsAfterCutoff(cutoff);
                return;
            }
        }

        if (p.y() < -gridHeight/2) {
            f->removePointsAfterCutoff(cutoff);
            return;
        }

        if (p.y() > gridHeight/2) {
            f->removePointsAfterCutoff(cutoff);
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
    int numOfObstacles = QRandomGenerator::global()->bounded(10);
    int generatedObstacles = 0;
    while(generatedObstacles < numOfObstacles) {
        Obstacle* obstacle = new Obstacle();

        obstacle->setCenter(randomPoint(width, height, 1.0));
        double newDiameter = obstacle->generateDiameter();
        obstacle->setDiameter(newDiameter);

        if (allowedObstacle(obstacle)) {
            obstacles.push_back(obstacle);
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

Player* WarGame::generatePlayer(int width, int height)
{
    Player *player = new Player("name");

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

    delete player0;
    delete player1;
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

void WarGame::switchPlayer()
{
    flipCanvas();
    drawCanvas();
    currentPlayer = 1 - currentPlayer;
}

void WarGame::on_back_war_button_clicked()
{
    cleanUp();
    emit backWarClicked();
    this->hide();
}

void WarGame::on_quit_war_button_clicked()
{
    ptrCheck->show();
}

//menjam
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
    else if(obj==ui->fire_war_button && event->type()==QEvent::Leave){
        ui->fire_war_button->setStyleSheet(fireStyle);
    }
    else if(obj==ui->quit_war_button && event->type()==QEvent::Leave){
        ui->quit_war_button->setStyleSheet(quitStyle);
    }
    else if(obj==ui->back_war_button && event->type()==QEvent::Leave){
        ui->back_war_button->setStyleSheet(backStyle);

    }

    return QDialog::eventFilter(obj,event);
}
