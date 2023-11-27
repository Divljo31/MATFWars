#include "testwindow.h"
#include "ui_testwindow.h"
#include "Canvas.h"
#include "Function.h"
#include "FunctionNode.h"

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

    const auto node = new FunctionNode(newFunction);

    emit newFunctionIsSet(node);
}

