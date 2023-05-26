#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();

    QString getTime();
    QString getLapsInfo();
    void nextLap();
    bool startStopToggle(); // переключает и возвр. состояние таймера
    void resetCounters();

private:
    QTimer *timer;
    uint32_t timeCount;     // счетчик 0,1 сек
    uint32_t prevTimeCount; // счетчик пройденного времени
    uint32_t lapsCount;     // счетчик кругов

    void timeCalc();

signals:
    void sig_time();
};

#endif // STOPWATCH_H
