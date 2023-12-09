#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QString>
#include <QElapsedTimer>
#include <QTimer>
#include <QLabel>
#include "ui_guessgame.h"

class Timer : public QThread{
    Q_OBJECT

public:
    Timer(QObject *parent = nullptr);
    int getSec(int s);
    void setInterface(Ui::GuessGame*);
    void showSec();
    void resetSec();
    void stopCount();
    void addSec(int);

protected:
    void run() override;
    QElapsedTimer *m_clock;
    Ui::GuessGame *m_interface;
    int m_sec = 10;

signals:
    void timerExpired();
};


#endif // TIMER_H
