#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TelemetryData.hpp"

MainWindow::MainWindow(SimulationController& controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(controller)     /* initialize controller reference to the one received from simulation engine */
{
    ui->setupUi(this);           /* load UI */
    connect(&controller, &SimulationController::telemetryUpdated, this, &MainWindow::onTelemetryUpdated);
    connect(ui->startButton, &QPushButton::clicked, this, [this, &controller] {    /*lambda connection */
        controller.start(); 
        ui->startButton->setEnabled(false); 
        ui->pauseButton->setEnabled(true); 
        ui->resumeButton->setEnabled(false); 
        ui->stopButton->setEnabled(true);
        ui->statusLabel->setText("Running"); // update status label
        });

    connect(ui->pauseButton, &QPushButton::clicked, this, [this, &controller] {
        controller.pause();
        ui->startButton->setEnabled(false);
        ui->pauseButton->setEnabled(false);
        ui->resumeButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
        ui->statusLabel->setText("Paused"); // update status label 
        });

    connect(ui->resumeButton, &QPushButton::clicked, this, [this, &controller] {
        controller.resume();
        ui->startButton->setEnabled(false);
        ui->pauseButton->setEnabled(true);
        ui->resumeButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->statusLabel->setText("Running");
        });
    
    connect(ui->stopButton, &QPushButton::clicked, this, [this, &controller] {
        controller.stop();
        ui->startButton->setEnabled(true);
        ui->pauseButton->setEnabled(false);
        ui->resumeButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
        ui->statusLabel->setText("Stopped"); // update status label 
        });
}

void MainWindow::onTelemetryUpdated(const TelemetryData& data) {
    ui->speedLabel->setText(QString::number(data.speed)); 
    ui->rpmLabel->setText(QString::number(data.rpm)); 
    ui->tempLabel->setText(QString::number(data.engineTemperature));
    
    // If you have a plot widget: 
    // ui->plot->addPoint(data.time, data.speed);
}

MainWindow::~MainWindow()
{
    delete ui;
}
