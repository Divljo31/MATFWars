#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
class QGraphicsScene;
class Function;
class FunctionNode;

namespace Ui {
class testWindow;
}

class testWindow : public QWidget
{
    Q_OBJECT

public:
    explicit testWindow(QWidget *parent = nullptr);
    ~testWindow();

signals:
    void newFunctionIsSet(FunctionNode*);

private slots:
    void setNewFunction();

private:
    Ui::testWindow *ui;
    QGraphicsScene *m_canvas;
    Function *m_function;
};

#endif // TESTWINDOW_H
