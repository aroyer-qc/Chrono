#include "counter.h"
#include <QDebug>
#include <QElapsedTimer>
#include <QLatin1Char>
#include <QThread>

Counter::Counter(QObject *parent) : QObject(parent)
{
    ResetChronometer();
}

void Counter::StartChronometer()
{
    QElapsedTimer Timer;

    Timer.start();
    QThread::msleep(20);
    Time += Timer.elapsed();
    MilliSeconds = Time % 1000;

    if(Time >= 1000)
    {
        Time = Time - 1000;
        Seconds++;
    }

    if(Seconds >= 60)
    {
        if(Time >= 1000)
        {
            Time = Time - 1000;
        }
        
        Seconds = 0;
        Minutes++;

        if(Minutes >= 1000)
        {
            ResetChronometer();
        }
    }

    emit ResultReady(QString("%3:%2:%1")
                         .arg(MilliSeconds/10,2,10,QLatin1Char('0'))
                         .arg(Seconds,2,10,QLatin1Char('0'))
                         .arg(Minutes,3,10,QLatin1Char(' ')));
}

void Counter::ResetChronometer()
{
    Minutes = 0;
    Seconds = 0;
    MilliSeconds = 0;
    Time = 0;
}
