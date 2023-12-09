#include "Timer.h"
#include <iostream>


Timer::Timer(QObject *parent)
    : QThread(parent)
{
}


void Timer::run(){
    m_clock = new QElapsedTimer();

    m_clock->start();
    showSec();

    while(m_sec >= 0){
        if(m_clock->elapsed() >= 1000){
            showSec();
            m_clock->start();
        }

        if(m_sec == 0){
            m_interface->timer_label->setText(" ");
            emit timerExpired();

            while(m_sec < 10){
                m_clock->start();
            }
        }
    }
}



void Timer::setInterface(Ui::GuessGame* ui){
    m_interface = ui;
}



void Timer::showSec(){
    m_interface->timer_label->setText(QString::number(m_sec >= 0 ? m_sec - 1 : 0));
    if(m_sec > 0){
        m_sec--;
    }
}


void Timer::resetSec(){
    m_sec = 11;
}


int Timer::getSec(int s){
    return s;
}

void Timer::stopCount(){
    m_sec = -1;
}

void Timer::addSec(int extra){
    if(m_sec + extra >= 11){
        m_sec = 11;
    }else{
        m_sec = m_sec + extra;
    }
}

