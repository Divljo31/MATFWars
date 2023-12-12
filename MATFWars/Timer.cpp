#include "Timer.h"
#include <iostream>


Timer::Timer(QObject *parent, int startSec)
    : QThread(parent),
    m_startSec(startSec)
{
}


void Timer::run(){
    m_clock = new QElapsedTimer();
//m_interface->timer_label->setText(QString::number(m_sec >= 0 ? m_sec - 1 : 0));
    m_clock->start();
    showSec();

    while(m_sec >= 0){
        if(m_clock->elapsed() >= 1000){
            showSec();
            m_clock->start();
        }

        if(m_sec == 0){
            emit timerExpired();

            while(m_sec < m_startSec){
                m_clock->start();
            }
        }
    }
}


void Timer::showSec(){
    //m_interface->timer_label->setText(QString::number(m_sec >= 0 ? m_sec - 1 : 0));

    if(m_sec > 0){
        m_sec--;
    }
    emit secPassed();
}

void Timer::resetSec(){
    m_sec = m_startSec + 1;
}


int Timer::getSec(){
    return m_sec;
}

void Timer::stopCount(){
    m_sec = -1;
}

void Timer::addSec(int extra){
    if(m_sec + extra > m_startSec){
        m_sec = m_startSec + 1;
    }else{
        m_sec = m_sec + extra;
    }
}

