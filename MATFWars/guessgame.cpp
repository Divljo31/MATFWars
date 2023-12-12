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
    m_timer = new Timer();

    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // signali i slotovi
    connect(ui->leFunctionInput, &QLineEdit::returnPressed, this, &GuessGame::setNewFunction);
    connect(this, &GuessGame::newFunctionIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::setFunction);
    connect(m_timer, SIGNAL(secPassed()), this, SLOT(showTime()));
    //connect(m_timer, SIGNAL(timerExpired()), this, SLOT(on_back_guess_button_clicked()));
}

void GuessGame::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);

    dynamic_cast<Canvas *>(m_canvas)->addCoordinateSystem();
    //setNewFunction();
}

void GuessGame::startGuessGame()
{
    m_timer->start();
    m_timer->resetSec();
    readFunctionsFromFile(":/functionSets/easyFunctionSet.txt");
    setNewFunction();
}

GuessGame::~GuessGame()
{
    delete ui;
    delete m_timer;
}

void GuessGame::on_back_guess_button_clicked()
{
    emit backGuessClicked();
    m_timer->stopCount();
    ui->timer_label->setText(" ");
    this->hide();
}

void GuessGame::showTime()
{
    ui->timer_label->setText(QString::number((m_timer->getSec()) >= 0 ? (m_timer->getSec()) : 0));
}

void GuessGame::setNewFunction()
{
    int index = chooseFunctionIndex();
    const auto functionString = m_functions[index];

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

int GuessGame::chooseFunctionIndex()
{
    int size = m_functions.size();
    return QRandomGenerator::global()->bounded(size);
}
