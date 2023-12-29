#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QString>
#include <QElapsedTimer>
#include <QTimer>
#include <QLabel>

class Timer : public QThread{
    Q_OBJECT

public:
    Timer(int startSec = 30, QObject *parent = nullptr);
    ~Timer();
    int getSec();
    void showSec();
    void resetSec();
    void stopCount();
    void addSec(int);

private:
    int m_startSec;

protected:
    void run() override;
    QElapsedTimer *m_clock;
    int m_sec;

signals:
    void timerExpired();
    void secPassed();
};


#endif // TIMER_H
