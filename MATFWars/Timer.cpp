#include "Timer.h"
#include <iostream>


Timer::Timer(QObject *parent)
    : QThread(parent)
{
}


void Timer::run(){
    m_sat = new QElapsedTimer();

    m_sat->start();
    ispisiVreme();

    while(m_sek >= 0){
        if(m_sat->elapsed() >= 1000){
            ispisiVreme();
            m_sat->start();
        }

        if(m_sek == 0){
            emit tajmerIstekao();
            m_interfejs->timer_label->setText("END");

            while(m_sek < 10){
                m_sat->start();
            }
        }
    }
}



void Timer::setInterfejs(Ui::GuessGame* ui){
    m_interfejs = ui;
}



void Timer::ispisiVreme(){
    m_interfejs->timer_label->setText(QString::number(m_sek >= 0 ? m_sek - 1 : 0));
    if(m_sek > 0){
        m_sek--;
    }
}


void Timer::resetujSek(){
    m_sek = 11;
}


int Timer::saljiSekunde(int s){
    return s;
}

void Timer::prekiniBrojanje(){
    m_sek = -1;
}

void Timer::dodajSekunde(int koliko){
    if(m_sek + koliko >= 11){
        m_sek = 11;
    }else{
        m_sek = m_sek + koliko;
    }
}

