#include "supercar_gui.h"
#include "ui_supercar_gui.h"

#include "Diagnostics.h"

#include <iostream>
#include "WorldViewer_Manager.h"
#include "DiagnosticsWindow.h"

extern Diagnostics diagnostics;


SuperCarMain_GUI::SuperCarMain_GUI(simulation::SimulationManager* simulationManager, WorldViewerManager* viewerManager, QWidget* parent) :
    simulationManager(simulationManager),
    viewerManager(viewerManager),
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

    // menu show world viewer toggle
    connect(ui->actionWorld_Viewer, &QAction::toggled, this, &SuperCarMain_GUI::showViewerToggled);

    connect(ui->actionDiagnostics_Window, &QAction::toggled, this, &SuperCarMain_GUI::showDiagnosticsToggled);

    
}

SuperCarMain_GUI::~SuperCarMain_GUI()
{
    diagnostics.log("SuperCarMain_GUI destructor called", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    if(diagnosticsWindow) delete diagnosticsWindow;
    delete ui;
}


void SuperCarMain_GUI::simulationBegin() {
    diagnostics.log("call to simulationBegin()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->beginSimulation();

    ui->begin->setEnabled(false);
    ui->end->setEnabled(true);

    ui->play->setEnabled(true);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(false);
}

void SuperCarMain_GUI::simulationEnd() {
    diagnostics.log("Call to simulationEnd()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->endSimulation();

    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);

    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(true);
}

void SuperCarMain_GUI::simulationPlay() {
    diagnostics.log("Call to simulationPlay()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->playSimulation();
    
    ui->play->setEnabled(false);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationPause() {
    diagnostics.log("Call to simulationPause()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->pauseSimulation();

    ui->play->setEnabled(true);
    ui->pause->setEnabled(true);
}

void SuperCarMain_GUI::simulationAddElement() {
    diagnostics.log("Call to simulationAddElement()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    static int id = 0;
    std::string type = this->ui->cb_newElementType->currentText().toStdString();
    if (type == "Car_SUV") {
        Eigen::Vector3d position(id, 0, 0);
        Eigen::Quaterniond orientation(1.0, 0.0, 0.0, 0.0);
        this->simulationManager->simulatedWorld->addElement(simulation::SimulationElement_Car(id++,simulation::CarModels::SUV));
    }
    else if (type == "Car_Sport") {
        Eigen::Vector3d position(id, 0, 0);
        Eigen::Quaterniond orientation(1.0, 0.0, 0.0, 0.0);
        this->simulationManager->simulatedWorld->addElement(simulation::SimulationElement_Car(id++, simulation::CarModels::Sport));
    }
    else if (type == "Car_Hatchback") {
        Eigen::Vector3d position(id, 0, 0);
        Eigen::Quaterniond orientation(1.0, 0.0, 0.0, 0.0);
        this->simulationManager->simulatedWorld->addElement(simulation::SimulationElement_Car(id++, simulation::CarModels::Hatchback));
    }
    else if (type == "Car_Minivan") {
        Eigen::Vector3d position(id, 0, 0);
        Eigen::Quaterniond orientation(1.0, 0.0, 0.0, 0.0);
        this->simulationManager->simulatedWorld->addElement(simulation::SimulationElement_Car(id++, simulation::CarModels::Minivan));
    }
    else if (type == "Box") {
        std::string name("Box");
        Eigen::Vector3d position(id, 0, 0);
        Eigen::Quaterniond orientation(1.0, 0.0, 0.0, 0.0);
        double mass = 10.0;
        this->simulationManager->simulatedWorld->addElement(simulation::SimulationElement(id++, name, position, orientation, mass));
    }
    else {
        diagnostics.log("Invalid type selected for new element.", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Error);
    }
    std::string elementsListText;
    this->simulationManager->simulatedWorld->applyToElements([&elementsListText](simulation::SimulationElement* element) {
        elementsListText += std::string(std::to_string(element->id) + " - " + element->name + "\n");
    });
    this->ui->te_list->setText(QString::fromStdString(elementsListText));
}




void SuperCarMain_GUI::simulationCycleTimeChanged(int newTime) {
    diagnostics.log("Call to simulationCycleTimeChanged()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    if (newTime > 0 && newTime < 1000) {
        this->simulationManager->simulationController.setSimulationIntervalMillis(newTime);
        diagnostics.monitor("Simulation Interval", std::to_string(newTime));
    }
}


void SuperCarMain_GUI::showDiagnosticsToggled(bool value) {
    if (value) {
        diagnosticsWindow = new DiagnosticsWindow(&diagnostics);
        diagnosticsWindow->move(this->width() + 10, 0);
        diagnosticsWindow->show();
    }
    else
    {
        if (diagnosticsWindow) {
            delete diagnosticsWindow;
        }
    }
}


void SuperCarMain_GUI::showViewerToggled(bool value) {
    if (value) {
        viewerManager->initializeWorldView();
    }
    else {
        viewerManager->terminateWorldView();  
    }
}
