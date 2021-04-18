#include "SuperCarWindow.h"
#include "ui_SuperCarWindow.h"

#include "Diagnostics.h"

#include <iostream>
#include "WorldViewer_Manager.h"
#include "DiagnosticsWindow.h"

extern Diagnostics diagnostics;


SuperCarWindow::SuperCarWindow(simulation::SimulationManager* simulationManager, WorldViewerManager* viewerManager, QWidget* parent) :
    simulationManager(simulationManager),
    viewerManager(viewerManager),
    diagnosticsWindow(nullptr),
    QMainWindow(parent),
    ui(new Ui::SuperCarWindow)
{
    diagnostics.log("SuperCarWindow constructor called", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    ui->setupUi(this);
    
    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);
    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->cycleTime->setEnabled(true);

    //Begin - End
    connect(ui->begin,  &QPushButton::clicked, this, &SuperCarWindow::simulationBegin);
    connect(ui->end,    &QPushButton::clicked, this, &SuperCarWindow::simulationEnd);

    //Play - Pause
    connect(ui->play,   &QPushButton::clicked, this, &SuperCarWindow::simulationPlay);
    connect(ui->pause,  &QPushButton::clicked, this, &SuperCarWindow::simulationPause);

    //Add
    connect(ui->add, &QPushButton::clicked, this, &SuperCarWindow::simulationAddElement);

    //Cycle Time
    connect(ui->cycleTime, QOverload<int>::of(&QSpinBox::valueChanged), this, &SuperCarWindow::simulationCycleTimeChanged);

    // menu show world viewer toggle
    connect(ui->actionWorld_Viewer, &QAction::toggled, this, &SuperCarWindow::showViewerToggled);

    connect(ui->actionDiagnostics_Window, &QAction::toggled, this, &SuperCarWindow::showDiagnosticsToggled);

    int simulationInterval = simulationManager->simulationController.getSimulationIntervalMillis();
    ui->cycleTime->setValue(simulationInterval);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&SuperCarWindow::updateInputCommands));
    timer->start(simulationInterval);
}


void SuperCarWindow::updateInputCommands() {
    int elementIndex = ui->sb_controls_id->value();
    if (elementIndex <= 0) return;
    simulation::SimulationElement* element = this->simulationManager->simulatedWorld->getElementAtIndex(elementIndex);
    if (element == nullptr) return;
    if (typeid(*element) == typeid(simulation::SimulationElement_Car)) {
        simulation::SimulationElement_Car* element_casted = dynamic_cast<simulation::SimulationElement_Car*>(element);
        element_casted->setAcceleratorPedal(static_cast<double>(ui->vs_accelerator->value())/1000);
        element_casted->setSteering(static_cast<double>(ui->hs_steering->value())/1000);
    }
}

void SuperCarWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Closing SuperCar",
        tr("Are you sure you want to exit?\n"),
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    }
    else {
        event->accept();
        diagnosticsWindow->close();
    }
}

SuperCarWindow::~SuperCarWindow()
{
    diagnostics.log("SuperCarWindow destructor called", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    delete ui;
}


void SuperCarWindow::simulationBegin() {
    diagnostics.log("call to simulationBegin()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->beginSimulation();

    ui->begin->setEnabled(false);
    ui->end->setEnabled(true);

    ui->play->setEnabled(true);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(false);
}

void SuperCarWindow::simulationEnd() {
    diagnostics.log("Call to simulationEnd()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->endSimulation();

    ui->begin->setEnabled(true);
    ui->end->setEnabled(false);

    ui->play->setEnabled(false);
    ui->pause->setEnabled(false);

    ui->cycleTime->setEnabled(true);
}

void SuperCarWindow::simulationPlay() {
    diagnostics.log("Call to simulationPlay()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->playSimulation();
    
    ui->play->setEnabled(false);
    ui->pause->setEnabled(true);
}

void SuperCarWindow::simulationPause() {
    diagnostics.log("Call to simulationPause()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);

    this->simulationManager->pauseSimulation();

    ui->play->setEnabled(true);
    ui->pause->setEnabled(true);
}

void SuperCarWindow::simulationAddElement() {
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




void SuperCarWindow::simulationCycleTimeChanged(int newTime) {
    diagnostics.log("Call to simulationCycleTimeChanged()", Diagnostics::Topic::Gui, Diagnostics::Verbosity::Debug);
    if (newTime > 0 && newTime < 1000) {
        this->simulationManager->simulationController.setSimulationIntervalMillis(newTime);
        diagnostics.monitor("Simulation Interval", std::to_string(newTime));
    }
}


void SuperCarWindow::showDiagnosticsToggled(bool value) {
    if (value) {
        diagnosticsWindow = new DiagnosticsWindow(&diagnostics);
        diagnosticsWindow->move(this->width() + 10, 0);
        diagnosticsWindow->show();
    }
    else
    {
        if (diagnosticsWindow) {
            diagnosticsWindow->close();
            delete diagnosticsWindow;
            diagnosticsWindow = nullptr;
        }
    }
}


void SuperCarWindow::showViewerToggled(bool value) {
    if (value) {
        viewerManager->initializeWorldView();
    }
    else {
        viewerManager->terminateWorldView();  
    }
}
