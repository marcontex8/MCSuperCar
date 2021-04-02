#ifndef SUPERCAR_GUI_H
#define SUPERCAR_GUI_H

#include <QMainWindow>
#include "SimulationManager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SuperCarMain_GUI; }
QT_END_NAMESPACE

// The following declarations are workarounds to avoid #include "WorldViewer_Manager.h" and #include "DiagnosticsWindow.h", that cause a problem because of glad.h
class WorldViewerManager;
class DiagnosticsWindow;

class SuperCarMain_GUI : public QMainWindow
{
    Q_OBJECT

public:
    SuperCarMain_GUI(simulation::SimulationManager* simulationManager, WorldViewerManager* viewerManager, QWidget *parent = nullptr);
    ~SuperCarMain_GUI();

private:
    Ui::SuperCarMain_GUI*ui;
    simulation::SimulationManager* simulationManager;
    WorldViewerManager* viewerManager;
    DiagnosticsWindow* diagnosticsWindow;
    const std::vector<std::string> getElementsList();


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
#endif // SUPERCAR_GUI_H
