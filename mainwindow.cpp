#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stopwatch = new Stopwatch(this);

    ui->pb_startPause->setText("Старт");
    ui->pb_lap->setText("Круг");
    ui->pb_lap->setDisabled(true);
    ui->pb_reset->setText("Сброс");
    //ui->pb_reset->setDisabled(true);

    ui->txtb_timeLaps->setReadOnly(true);

    showTime();
    connect(stopwatch, &Stopwatch::sig_time, this, &MainWindow::showTime);

    // Старт/Пауза
    connect(ui->pb_startPause, &QPushButton::clicked, this, [this]{
        bool isStart(stopwatch->startStopToggle());
        if (isStart)
        {
            ui->pb_startPause->setText("Пауза");
        }
        else ui->pb_startPause->setText("Старт");

        ui->pb_lap->setDisabled(!isStart);
    });

    // Круг
    connect(ui->pb_lap, &QPushButton::clicked, this, [this]{
        stopwatch->nextLap();
        ui->txtb_timeLaps->append(stopwatch->getLapsInfo());
    });

    // Сброс
    connect(ui->pb_reset, &QPushButton::clicked, this, [this]{
        stopwatch->resetCounters();
        showTime();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    ui->lb_time->setText(stopwatch->getTime());
    ui->pb_reset->setDisabled(stopwatch->timeNotNull());
}

