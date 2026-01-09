#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TelemetryData.hpp"
#include <QDateTime>

MainWindow::MainWindow(SimulationController& controller, QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, controller(controller)     /* initialize controller reference to the one received from simulation engine */
{
	ui->setupUi(this);           /* load UI */

	startTimeMs = QDateTime::currentMSecsSinceEpoch();

	// ---------------- RPM CHART ---------------- 
	rpmSeries = new QLineSeries();
	rpmSeries->setUseOpenGL(true);
	rpmChart = new QChart();
	rpmChart->addSeries(rpmSeries);

	rpmAxisX = new QValueAxis();
	rpmAxisY = new QValueAxis();

	rpmAxisX->setRange(0, 60);
	rpmAxisY->setRange(0, 8000);

	rpmAxisX->setTitleText("Time (ticks)");
	rpmAxisY->setTitleText("RPM");

	rpmChart->addAxis(rpmAxisX, Qt::AlignBottom);
	rpmChart->addAxis(rpmAxisY, Qt::AlignLeft);

	rpmSeries->attachAxis(rpmAxisX);
	rpmSeries->attachAxis(rpmAxisY);

	ui->rpmChartView->setChart(rpmChart);


	// ---------------- SPEED CHART ---------------- 
	speedSeries = new QLineSeries();
	speedSeries->setUseOpenGL(true);
	speedChart = new QChart();
	speedChart->addSeries(speedSeries);

	speedAxisX = new QValueAxis();
	speedAxisY = new QValueAxis();

	speedAxisX->setRange(0, 60);
	speedAxisY->setRange(0, 240); // km/h  

	speedAxisX->setTitleText("Time (ticks)");
	speedAxisY->setTitleText("km/h");

	speedChart->addAxis(speedAxisX, Qt::AlignBottom);
	speedChart->addAxis(speedAxisY, Qt::AlignLeft);

	speedSeries->attachAxis(speedAxisX);
	speedSeries->attachAxis(speedAxisY);

    ui->vehSpdChartView->setChart(speedChart);

	// ---------------- ENGINE TEMP CHART ---------------- 
	engineTempSeries = new QLineSeries();
	engineTempSeries->setUseOpenGL(true);
	engineTempChart = new QChart();
	engineTempChart->addSeries(engineTempSeries);

	engineTempAxisX = new QValueAxis();
	engineTempAxisY = new QValueAxis();

	engineTempAxisX->setRange(0, 60);
	engineTempAxisY->setRange(0, 150); // �C 

	engineTempAxisX->setTitleText("Time (ticks)");
	engineTempAxisY->setTitleText("deg C");

	engineTempChart->addAxis(engineTempAxisX, Qt::AlignBottom);
	engineTempChart->addAxis(engineTempAxisY, Qt::AlignLeft);

	engineTempSeries->attachAxis(engineTempAxisX);
	engineTempSeries->attachAxis(engineTempAxisY);

	ui->engineTempChartView->setChart(engineTempChart);

	// ---------------- BATTERY VOLTAGE CHART ---------------- 
	batteryVoltSeries = new QLineSeries();
	batteryVoltSeries->setUseOpenGL(true);
	batteryVoltChart = new QChart();
	batteryVoltChart->addSeries(batteryVoltSeries);

	batteryVoltAxisX = new QValueAxis();
	batteryVoltAxisY = new QValueAxis();

	batteryVoltAxisX->setRange(0, 60);
	batteryVoltAxisY->setRange(0, 20); // volts 

	batteryVoltAxisX->setTitleText("Time (ticks)");
	batteryVoltAxisY->setTitleText("V");

	batteryVoltChart->addAxis(batteryVoltAxisX, Qt::AlignBottom);
	batteryVoltChart->addAxis(batteryVoltAxisY, Qt::AlignLeft);

	batteryVoltSeries->attachAxis(batteryVoltAxisX);
	batteryVoltSeries->attachAxis(batteryVoltAxisY);

	ui->batVoltChartView->setChart(batteryVoltChart);

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
	ui->speedLabel->setText(QString::number(data.vehicleSpeed));
	ui->rpmLabel->setText(QString::number(data.rpm));
    ui->tempLabel->setText(QString::number(data.engineTemperature));
	ui->batteryVoltageLabel->setText(QString::number(data.batteryVoltage));

	qint64 nowMs = QDateTime::currentMSecsSinceEpoch(); 
	qreal t = (nowMs - startTimeMs) / 1000.0; // seconds since start
	qreal window = 60.0; // 60-second sliding window
	
	// Append points + slide axis for each chart
	// RPM 
	rpmSeries->append(t, data.rpm);
	if (t >= window)
		rpmAxisX->setRange(t - window, t); // slide X axis
	else
		rpmAxisX->setRange(0, window);
	while (!rpmSeries->points().isEmpty() &&
		rpmSeries->points().first().x() < t - window) { // Remove old points (older than 60 seconds) 
		rpmSeries->remove(0);
	}
	
	// Speed 
	speedSeries->append(t, data.vehicleSpeed);
	if (t >= window)
		speedAxisX->setRange(t - window, t);
	else 
		speedAxisX->setRange(0, window);
	while (!speedSeries->points().isEmpty() &&
		speedSeries->points().first().x() < t - window) { // Remove old points (older than 60 seconds) 
		speedSeries->remove(0);
	}
	
	// Engine Temperature 
	engineTempSeries->append(t, data.engineTemperature);
	if (t >= window)
		engineTempAxisX->setRange(t - window, t);
	else
		engineTempAxisX->setRange(0, window);	
	while (!engineTempSeries->points().isEmpty() &&
		engineTempSeries->points().first().x() < t - window) { // Remove old points (older than 60 seconds) 
		engineTempSeries->remove(0);
	}
	
	// Battery Voltage 
	batteryVoltSeries->append(t, data.batteryVoltage);
	if (t >= window)
		batteryVoltAxisX->setRange(t - window, t);
	else
		batteryVoltAxisX->setRange(0, window);
	while (!batteryVoltSeries->points().isEmpty() &&
		batteryVoltSeries->points().first().x() < t - window) { // Remove old points (older than 60 seconds) 
		batteryVoltSeries->remove(0);
	}

	// If you have a plot widget: 
	// ui->plot->addPoint(data.time, data.speed);
}

MainWindow::~MainWindow()
{
	delete ui;
}
