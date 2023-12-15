#ifndef GUESSGAME_H
#define GUESSGAME_H

#include <QDialog>
#include <QShowEvent>
#include "Function.h"
#include "FunctionNode.h"
#include "Canvas.h"
#include "Timer.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRandomGenerator>
#include "Difficulty.h"

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
    void drawCurrentFunction();
    void chooseFunctionIndex();
    void showTime();
    void checkAnswerAndSetNewFunction();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void readFunctionsFromFile(std::string fileName);


private:
    Ui::GuessGame *ui;
    Timer *m_timer;
    QGraphicsScene *m_canvas;
    std::vector<std::string> m_functions;
    std::unordered_set<int> m_usedFunctions;
    int m_currentFunctionIndex = -1;
    int m_score = 0;
    difficulty m_diff = easy;


};

#endif // GUESSGAME_H
