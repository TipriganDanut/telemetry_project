#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots: void onTelemetryUpdated(const TelemetryData& data);
};
#endif // MAINWINDOW_H
