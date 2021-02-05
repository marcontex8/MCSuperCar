#include "supercar_gui.h"
#include "./ui_supercar_gui.h"

#include "Diagnostics.h"

#include <iostream>

extern Diagnostics diagnostics;


SuperCarMain_GUI::SuperCarMain_GUI(simulation::SimulationManager* manager, QWidget* parent) :
    manager(manager),
    QMainWindow(parent),
    ui(new Ui::SuperCarMain_GUI)
{
    diagnostics.log("SuperCarMain_GUI constructor called", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    ui->setupUi(this);
    
    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);
    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->cycleTime->setEnabled(true);

    // Initializing and connecting GUI with simulation elements
    elementsListModel = new SimulationElementListModel(manager->simulatedWorld);
    ui->elements_list_view->setModel(elementsListModel);

    //Begin - End
    connect(ui->begin,  &QPushButton::clicked, this, &SuperCarMain_GUI::simulationBegin);
    connect(ui->end,    &QPushButton::clicked, this, &SuperCarMain_GUI::simulationEnd);

    //Play - Pause
    connect(ui->play,   &QPushButton::clicked, this, &SuperCarMain_GUI::simulationPlay);
    connect(ui->pause,  &QPushButton::clicked, this, &SuperCarMain_GUI::simulationPause);

    //Add
    connect(ui->add, &QPushButton::clicked, this, &SuperCarMain_GUI::simulationAddElement);

    //Cycle Time
    connect(ui->cycleTime, QOverload<int>::of(&QSpinBox::valueChanged), this, &SuperCarMain_GUI::simulationCycleTimeChanged);

}

SuperCarMain_GUI::~SuperCarMain_GUI()
{
    diagnostics.log("SuperCarMain_GUI destructor called", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    delete ui;
}


void SuperCarMain_GUI::simulationBegin() {
    diagnostics.log("call to simulationBegin()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->manager->beginSimulation();

    ui->begin->setEnabled(false);
    ui->end->setEnabled(true);

    ui->play->setEnabled(true);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(false);
}

void SuperCarMain_GUI::simulationEnd() {
    diagnostics.log("Call to simulationEnd()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->manager->endSimulation();

    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);

    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(true);
}

void SuperCarMain_GUI::simulationPlay() {
    diagnostics.log("Call to simulationPlay()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->manager->playSimulation();
    
    ui->play->setEnabled(false);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationPause() {
    diagnostics.log("Call to simulationPause()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->manager->pauseSimulation();

    ui->play->setEnabled(true);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationAddElement() {
    diagnostics.log("Call to simulationAddElement()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    static int id = 0;
    std::string name("elemento");
    Eigen::Vector3d position(0,0,0);
    Eigen::Quaterniond orientation;
    double mass = 10.0;
    this->manager->simulatedWorld->addElement(simulation::SimulationElement(id++, name, position, orientation, mass));
    QString result = "New Element Added";
    emit elementsListModel->layoutChanged();
        //editCompleted(result);
}



void SuperCarMain_GUI::simulationCycleTimeChanged(int newTime) {
    diagnostics.log("Call to simulationCycleTimeChanged()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    if (newTime > 0 && newTime < 1000) {
        this->manager->simulationController.setSimulationIntervalMillis(newTime);
        diagnostics.monitor("Simulation Interval", std::to_string(newTime));
    }
}