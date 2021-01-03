#ifndef SUPERCAR_GUI_H
#define SUPERCAR_GUI_H

#include <QMainWindow>
#include "SimulationManager.h"
#include "SimulationElementListModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SuperCarMain_GUI; }
QT_END_NAMESPACE

class SuperCarMain_GUI : public QMainWindow
{
    Q_OBJECT

public:
    SuperCarMain_GUI(simulation::SimulationManager* manager, QWidget *parent = nullptr);
    ~SuperCarMain_GUI();

private:
    Ui::SuperCarMain_GUI*ui;
    simulation::SimulationManager* manager;
    SimulationElementListModel* elementsListModel;

private slots:
    void simulationBegin();
    void simulationEnd();

    void simulationPlay();
    void simulationPause();

    void simulationAddElement();

    void simulationCycleTimeChanged(int newTime);
};
#endif // SUPERCAR_GUI_H
