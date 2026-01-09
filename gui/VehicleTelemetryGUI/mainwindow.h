#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart> 
#include <QtCharts/QChartView> 
#include <QtCharts/QLineSeries> 
#include <QtCharts/QValueAxis>

#include "SimulationController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SimulationController& controller, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SimulationController& controller;

    qint64 startTimeMs;

    // --- Charts --- //
    //**Engine RPM chart** 
    QChart* rpmChart; 
    QLineSeries* rpmSeries; 
    QValueAxis* rpmAxisX; 
    QValueAxis* rpmAxisY; 
    
    // **Vehicle Speed chart** 
    QChart* speedChart; 
    QLineSeries* speedSeries; 
    QValueAxis* speedAxisX;
    QValueAxis* speedAxisY; 
    
    // **Engine Temperature chart** 
    QChart* engineTempChart; 
    QLineSeries* engineTempSeries; 
    QValueAxis* engineTempAxisX; 
    QValueAxis* engineTempAxisY; 
    
    // **Battery Voltage chart** 
    QChart* batteryVoltChart; 
    QLineSeries* batteryVoltSeries; 
    QValueAxis* batteryVoltAxisX; 
    QValueAxis* batteryVoltAxisY;

private slots: 
    void onTelemetryUpdated(const TelemetryData& data);
};
#endif // MAINWINDOW_H
