#include "supercar_gui.h"
#include "./ui_supercar_gui.h"

#include <iostream>

SuperCarMain_GUI::SuperCarMain_GUI(simulation::SimulationManager* manager, QWidget* parent) :
    manager(manager),
    QMainWindow(parent),
    ui(new Ui::SuperCarMain_GUI)
{
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
    delete ui;
}


void SuperCarMain_GUI::simulationBegin() {
    this->manager->beginSimulation();

    ui->begin->setEnabled(false);
    ui->end->setEnabled(true);

    ui->play->setEnabled(true);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(false);
}

void SuperCarMain_GUI::simulationEnd() {
    this->manager->endSimulation();

    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);

    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(true);
}

void SuperCarMain_GUI::simulationPlay() {
    this->manager->playSimulation();
    
    ui->play->setEnabled(false);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationPause() {
    this->manager->pauseSimulation();

    ui->play->setEnabled(true);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationAddElement() {
    this->manager->simulatedWorld->addElement(simulation::SimulationElement());
    std::cout << "New Element Added." << std::endl;
    QString result = "New Element Added";
    emit elementsListModel->layoutChanged();
        //editCompleted(result);
}



void SuperCarMain_GUI::simulationCycleTimeChanged(int newTime) {
    if (newTime > 0 && newTime < 1000) {
        this->manager->simulationController.setSimulationIntervalMillis(newTime);
        std::cout << "Simulation Cycle Time Changed to " << newTime << std::endl;
    }
}