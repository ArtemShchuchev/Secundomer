#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject{parent}, timeCount(0), prevTimeCount(0), lapsCount(0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::timeCalc);
}

Stopwatch::~Stopwatch(){}

QString Stopwatch::getTime()
{
    uint32_t    min(timeCount / 600),
                sec(timeCount / 10 - min * 60),
                split(timeCount % 10);

    QString timeStr = (min < 10) ? "0" : "";
    timeStr += QString::number(min) + ":";
    if (sec < 10)
    {
        timeStr += "0";
    }
    timeStr += QString("%1.%2").arg(sec).arg(split);

    return timeStr;
}

QString Stopwatch::getLapsInfo()
{
    QString mes(QString("Круг %1, время: %2.%3 сек")
                .arg(lapsCount)
                .arg((timeCount - prevTimeCount) / 10)
                .arg((timeCount - prevTimeCount) % 10)
                );

    prevTimeCount = timeCount;
    return mes;
}

void Stopwatch::nextLap()
{
    ++lapsCount;
}

void Stopwatch::timeCalc()
{
    ++timeCount;
    emit sig_time();    // сигнал о изменении времени
}

bool Stopwatch::startStopToggle()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    else timer->start(100);

    return timer->isActive();
}

void Stopwatch::resetCounters()
{
    timeCount = 0;
    prevTimeCount = 0;
    lapsCount = 0;
}
