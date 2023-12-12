#ifndef GUESSGAME_H
#define GUESSGAME_H

#include <QDialog>
#include <QShowEvent>
#include "Function.h"
#include "FunctionNode.h"
#include "Canvas.h"
#include "Timer.h"

class QGraphicsScene;
class Function;
class FunctionNode;

namespace Ui {
class GuessGame;
}

class GuessGame : public QDialog
{
    Q_OBJECT

public:
    explicit GuessGame(QWidget *parent = nullptr);
    void startGuessGame();
    ~GuessGame();

signals:
    void backGuessClicked();
    void newFunctionIsSet(FunctionNode*);

private slots:
    void on_back_guess_button_clicked();
    void setNewFunction();
    void showTime();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::GuessGame *ui;
    Timer *m_timer;
    QGraphicsScene *m_canvas;
};

#endif // GUESSGAME_H
