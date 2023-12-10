#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QShowEvent>
#include "Canvas.h"

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
    void windowOpened();

private slots:
    void setNewFunction();

// pri prikazivanju ekrana se odmah doda koordinatni sistem u kanvas koordinatni sistem
protected:
    void showEvent(QShowEvent *event) override {
        QWidget::showEvent(event);
        if (event->isAccepted()) {
            dynamic_cast<Canvas *>(m_canvas)->addCoordinateSystem();
        }
    }


private:
    Ui::testWindow *ui;
    QGraphicsScene *m_canvas;
    Function *m_function;
};

#endif // TESTWINDOW_H
