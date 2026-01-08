#include "mainwindow.h"
#include "Vehicle.hpp"
#include "TelemetryManager.hpp"
#include "SimulationController.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    Vehicle vehicle;
    TelemetryManager telemetry(vehicle);
    SimulationController controller(vehicle, telemetry);

    QApplication a(argc, argv);
    MainWindow mainWindow(controller);
    mainWindow.show();
    return a.exec();
}
