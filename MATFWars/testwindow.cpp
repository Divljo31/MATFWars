#include "testwindow.h"
#include "ui_testwindow.h"

#include "Function.h"
#include "FunctionNode.h"
#include "Player.h"
#include "PlayerNode.h"

testWindow::testWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testWindow),
    m_canvas(new Canvas(this))
{
    ui->setupUi(this);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setScene(m_canvas);
    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // signali i slotovi
    connect(ui->pbInput, &QPushButton::clicked, this, &testWindow::setNewFunction);
    connect(this, &testWindow::newFunctionIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::setFunction);
}

testWindow::~testWindow()
{
    delete ui;

    delete m_function;
}

void testWindow::setNewFunction()
{

    const auto functionString = ui->leFunctionInput->text();

    std::cout << functionString.toStdString() << std::endl;

    const auto newFunction = new Function(functionString.toStdString());
    newFunction->scaleToCanvas(m_canvas->width(), m_canvas->height(), dynamic_cast<Canvas *>(m_canvas)->gridWidth());
    newFunction->translatePointsObserverView(m_canvas->width()/2, m_canvas->height()/2);

    QRectF sceneRect = QRectF(m_canvas->sceneRect());

    const auto node = new FunctionNode(newFunction, sceneRect.width(), sceneRect.height());

    Player *p = new Player("2, 10");
    p->setCoordinates(QPointF(5, 3));
    PlayerNode* pw = new PlayerNode(p, m_canvas->width(), m_canvas->height());
    dynamic_cast<Canvas *>(m_canvas)->addItem(pw);

    emit newFunctionIsSet(node);
}

