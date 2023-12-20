#include "guessgame.h"
#include "ui_guessgame.h"
#include <iostream>

GuessGame::GuessGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessGame),
    m_canvas(new Canvas(this))
{
    ui->setupUi(this);
    m_timer = new Timer(50);

    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // signali i slotovi
    // FIX: pravi problem ako se oba prikljuce, salju se dupli signali
    // connect(ui->enter_guess_button, &QPushButton::clicked, this, &GuessGame::checkAnswerAndSetNewFunction);
    connect(ui->leFunctionInput, &QLineEdit::returnPressed, this, &GuessGame::checkAnswerAndSetNewFunction);

    connect(this, &GuessGame::newFunctionIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::setFunction);

    connect(m_timer, SIGNAL(secPassed()), this, SLOT(showTime()));
    connect(m_timer, SIGNAL(timerExpired()), this, SLOT(resultWindow()));

    ui->enter_guess_button->installEventFilter(this);
    ui->back_guess_button->installEventFilter(this);
    enterStyle=ui->enter_guess_button->styleSheet();
    backStyle=ui->back_guess_button->styleSheet();

    ptrResult=new Result();
}

void GuessGame::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);

    dynamic_cast<Canvas *>(m_canvas)->addCoordinateSystem();
    if (m_currentFunctionIndex != -1) drawCurrentFunction();

}

void GuessGame::startGuessGame()
{
    m_timer->start();
    m_timer->resetSec();

    // TODO: ovde uzeti difficulty iz prethodnog prozora i postaviti ga, vrv da se prosledi signalom, tj startGuessGame da prima (Difficulty d)
    // za sad je po defaultu m_diff = easy
    switch (m_diff) {
    case easy:
        readFunctionsFromFile(":/functionSets/easyFunctionSet.txt");
        break;
    case hard:
        readFunctionsFromFile(":/functionSets/hardFunctionSet.txt");
        break;
    }
    chooseFunctionIndex();
}

GuessGame::~GuessGame()
{
    delete ui;
    m_timer->deleteLater();


}

void GuessGame::on_back_guess_button_clicked()
{
    m_timer->stopCount();
    ui->timer_label->setText(" ");
    this->hide();



    //emit backGuessClicked();
}

void GuessGame::showTime()
{
    ui->timer_label->setText(QString::number((m_timer->getSec()) >= 0 ? (m_timer->getSec()) : 0));
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
}

void GuessGame::checkAnswerAndSetNewFunction()
{
    std::string answer = ui->leFunctionInput->text().toStdString();

    Function* currentFunction = new Function(m_functions[m_currentFunctionIndex]);
    Function* answerFunction = new Function(answer);

    ui->leFunctionInput->setText("");

    if (currentFunction->equals(answerFunction)) {

        m_score++;

        int extraTime = 2;
        m_timer->addSec(extraTime);

        ui->score_label->setText(QString::number(m_score));
        ui->gvCanvas->setBackgroundBrush(QBrush(Qt::green));
    }
    else {
        ui->gvCanvas->setBackgroundBrush(QBrush(Qt::red));
    }

    delete currentFunction;
    delete answerFunction;

    chooseFunctionIndex();
}


void GuessGame::chooseFunctionIndex()
{
    int size = m_functions.size();

    if (m_usedFunctions.size() == size) m_usedFunctions.clear();

    while(m_usedFunctions.count(m_currentFunctionIndex) > 0  || m_currentFunctionIndex == -1)
        m_currentFunctionIndex =  QRandomGenerator::global()->bounded(size);

    m_usedFunctions.insert(m_currentFunctionIndex);

    drawCurrentFunction();
}

void GuessGame::drawCurrentFunction()
{
    const auto functionString = m_functions[m_currentFunctionIndex];

    Function* newFunction = new Function(functionString);
    newFunction->scaleToCanvas(m_canvas->width(), m_canvas->height(), dynamic_cast<Canvas *>(m_canvas)->gridWidth());
    newFunction->translatePointsObserverView(m_canvas->width()/2, m_canvas->height()/2);

    QRectF sceneRect = QRectF(m_canvas->sceneRect());

    FunctionNode* node = new FunctionNode(newFunction, sceneRect.width(), sceneRect.height());

    emit newFunctionIsSet(node);
}

void GuessGame::readFunctionsFromFile(std::string fileName)
{
    QFile file(QString::fromStdString(fileName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString qLine = stream.readLine();
            std::string line = qLine.toStdString();
            m_functions.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

bool GuessGame::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->enter_guess_button && event->type()==QEvent::Enter){
        ui->enter_guess_button->setCursor(Qt::PointingHandCursor);
        ui->enter_guess_button->setStyleSheet(enterStyle+"border:7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->back_guess_button && event->type()==QEvent::Enter){
        ui->back_guess_button->setCursor(Qt::PointingHandCursor);
        ui->back_guess_button->setStyleSheet(backStyle+"border:7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->enter_guess_button && event->type()==QEvent::Leave){
        ui->enter_guess_button->setStyleSheet(enterStyle);
    }
    else if(obj==ui->back_guess_button && event->type()==QEvent::Leave){
        ui->back_guess_button->setStyleSheet(backStyle);
    }

    return QDialog::eventFilter(obj,event);
}

void GuessGame::resultWindow()
{
    ptrResult->show();
    this->hide();
}





