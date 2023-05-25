#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stopwatch = new Stopwatch(this);

    ui->pb_startPause->setText("Старт");
    isStartBtn = true;
    ui->pb_lap->setText("Круг");
    ui->pb_lap->setDisabled(true);
    ui->pb_reset->setText("Сброс");

    ui->txtb_timeLaps->setReadOnly(true);

    showTime();
    QObject::connect(stopwatch, &Stopwatch::sig_time, this, &MainWindow::showTime);

    // Старт/Пауза
    QObject::connect(ui->pb_startPause, &QPushButton::clicked, stopwatch, &Stopwatch::rcvBtnStart);
    QObject::connect(ui->pb_startPause, &QPushButton::clicked, this, [this]{
        if (isStartBtn)
        {
            ui->pb_startPause->setText("Пауза");
            ui->pb_lap->setDisabled(false);
        }
        else
        {
            ui->pb_startPause->setText("Старт");
            ui->pb_lap->setDisabled(true);
        }
        isStartBtn = !isStartBtn;
    });

    // Круг
    QObject::connect(ui->pb_lap, &QPushButton::clicked, stopwatch, &Stopwatch::rcvBtnLap);
    ///////////// Способ 1 (какой правильно?)
    QObject::connect(stopwatch, &Stopwatch::sig_laps, this, [this]{
        ui->txtb_timeLaps->append(stopwatch->getLapsInfo());
    });
    ///////////// Способ 2 (какой правильно?)
    /*QObject::connect(ui->pb_lap, &QPushButton::clicked, this, [this]{
        ui->txtb_timeLaps->append(stopwatch->getLapsInfo());
    });*/

    // Сброс
    QObject::connect(ui->pb_reset, &QPushButton::clicked, stopwatch, &Stopwatch::rcvBtnReset);
    QObject::connect(ui->pb_reset, &QPushButton::clicked, this, [this]{
        ui->pb_startPause->setText("Старт");
        ui->pb_lap->setDisabled(true);
        isStartBtn = true;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    ui->lb_time->setText(stopwatch->getTime());
}

