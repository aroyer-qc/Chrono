//-------------------------------------------------------------------------------------------------
//
// Copyright(c) 2025 Alain Royer.
// Email: aroyer.qc@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
// AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------------------------------

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
