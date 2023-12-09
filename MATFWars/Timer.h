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
    int saljiSekunde(int s);
    void setInterfejs(Ui::GuessGame*);
    void ispisiVreme();
    void resetujSek();
    void prekiniBrojanje();
    void dodajSekunde(int);

protected:
    void run() override;
    QElapsedTimer *m_sat;
    Ui::GuessGame *m_interfejs;
    int m_sek = 10;

signals:
    void tajmerIstekao();
};


#endif // TIMER_H
