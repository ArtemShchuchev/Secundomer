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

private:
    QTimer *timer;
    unsigned int timeCount;     // счетчик 0,1 сек
    unsigned int prevTimeCount; // счетчик пройденного времени
    unsigned int lapsCount;     // счетчик кругов
    void timeCalc();

signals:
    void sig_time();
    void sig_laps();

public slots:
    void rcvBtnStart();
    void rcvBtnLap();
    void rcvBtnReset();
};

#endif // STOPWATCH_H
