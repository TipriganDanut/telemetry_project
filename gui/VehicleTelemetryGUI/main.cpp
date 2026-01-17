#include "mainwindow.h"
#include "Vehicle.hpp"
#include "TelemetryManager.hpp"
#include "Database.h"
#include "TelemetryRepository.h"
#include "SimulationController.hpp"
#include "PersistenceObserver.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    Vehicle vehicle;
    TelemetryManager telemetry(vehicle);
    Database db("telemetry.db");
    TelemetryRepository repo(db);
    SimulationController controller(vehicle, telemetry, repo);
    PersistenceObserver persistenceObs(repo);
    controller.attach(&persistenceObs);

    QApplication a(argc, argv);
    MainWindow mainWindow(controller);
    mainWindow.show();
    return a.exec();
}
