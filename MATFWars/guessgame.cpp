#include "guessgame.h"
#include "ui_guessgame.h"
#include <iostream>

using namespace std;
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
    connect(m_timer, SIGNAL(timerExpired()), this, SLOT(on_back_guess_button_clicked()));
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
    readFunctionsFromFile(":/functionSets/easyFunctionSet.txt");
    chooseFunctionIndex();
}

GuessGame::~GuessGame()
{
    delete ui;
    delete m_timer;
}

void GuessGame::on_back_guess_button_clicked()
{
    m_timer->stopCount();
    ui->timer_label->setText(" ");
    this->hide();

    emit backGuessClicked();
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
        // ako treba dodati vreme na tajmer
        ui->gvCanvas->setBackgroundBrush(QBrush(Qt::green));
        cout << m_score << endl;
    }
    else {
        cout << "nope" << endl;
        ui->gvCanvas->setBackgroundBrush(QBrush(Qt::red));
    }

    delete currentFunction;
    delete answerFunction;

    chooseFunctionIndex();
}

void GuessGame::chooseFunctionIndex()
{
    int size = m_functions.size();
    m_currentFunctionIndex =  QRandomGenerator::global()->bounded(size);

    drawCurrentFunction();
}

void GuessGame::drawCurrentFunction()
{
    const auto functionString = m_functions[m_currentFunctionIndex];

    const auto newFunction = new Function(functionString);
    newFunction->scaleToCanvas(m_canvas->width(), m_canvas->height(), dynamic_cast<Canvas *>(m_canvas)->gridWidth());
    newFunction->translatePointsObserverView(m_canvas->width()/2, m_canvas->height()/2);

    QRectF sceneRect = QRectF(m_canvas->sceneRect());

    const auto node = new FunctionNode(newFunction, sceneRect.width(), sceneRect.height());

    emit newFunctionIsSet(node);
}

void GuessGame::readFunctionsFromFile(string fileName)
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

