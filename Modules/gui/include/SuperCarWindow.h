#ifndef SUPERCARWINDOW_H
#define SUPERCARWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>


#include "SimulationManager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SuperCarWindow; }
QT_END_NAMESPACE

// The following declarations are workarounds to avoid #include "WorldViewer_Manager.h" and #include "DiagnosticsWindow.h", that cause a problem because of glad.h
class WorldViewerManager;
class DiagnosticsWindow;

class SuperCarWindow : public QMainWindow
{
    Q_OBJECT

public:
    SuperCarWindow(simulation::SimulationManager* simulationManager, WorldViewerManager* viewerManager, QWidget *parent = nullptr);
    ~SuperCarWindow();

private:
    Ui::SuperCarWindow*ui;
    simulation::SimulationManager* simulationManager;
    WorldViewerManager* viewerManager;
    DiagnosticsWindow* diagnosticsWindow;
    const std::vector<std::string> getElementsList();
    void closeEvent(QCloseEvent* event);



private slots:
    void simulationBegin();
    void simulationEnd();

    void simulationPlay();
    void simulationPause();

    void simulationAddElement();

    void simulationCycleTimeChanged(int newTime);

    void showDiagnosticsToggled(bool value);
    void showViewerToggled(bool value);

};
#endif // SUPERCARWINDOW_H
