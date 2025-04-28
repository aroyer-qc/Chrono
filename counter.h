#pragma once

#include <QObject>
#include <QMutex>
#include <QTime>

class Counter : public QObject
{
    Q_OBJECT
    public:
        explicit Counter(QObject *parent = 0);

    signals:
        void ResultReady(QString Result);
        void Finished();

    public slots:
        void StartChronometer();
        void ResetChronometer();

    private:
        QTime Timer;
       // bool StartFlag;
       // bool StopFlag;
//        long End;
        uint Time;
        uint Minutes;
        uint Seconds;
        uint MilliSeconds;
};

