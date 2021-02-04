#include "DiagnosticsWindow.h"
#include "ui_DiagnosticsWindow.h"


DiagnosticsWindow::DiagnosticsWindow(Diagnostics* diagnostics, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DiagnosticsWindow),
    diagnostics(diagnostics)
{
    ui->setupUi(this);
    /*
    guiLogsListModel = new LogsListModel(diagnostics, Diagnostics::Topic::Gui);
    ui->lv_GUI_logs->setModel(guiLogsListModel);
    simulatorLogsListModel = new LogsListModel(diagnostics, Diagnostics::Topic::Simulation);
    ui->lv_simulation_logs->setModel(simulatorLogsListModel);
    viewerLogsListModel = new LogsListModel(diagnostics, Diagnostics::Topic::Viewer);
    ui->lv_viewer_logs->setModel(viewerLogsListModel);
    */
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&DiagnosticsWindow::updateLogs));
    timer->start(1000);
}

DiagnosticsWindow::~DiagnosticsWindow()
{
    delete ui;
    //delete guiLogsListModel;
    //delete simulatorLogsListModel;
    //delete viewerLogsListModel;
}

void DiagnosticsWindow::updateLogs() {
    std::string lastSimulationLog = diagnostics->readFromQueue(Diagnostics::Topic::Simulation);
    while (lastSimulationLog != "")
    {
        ui->lw_simulation_logs->addItem(QString::fromStdString(lastSimulationLog));
        lastSimulationLog = diagnostics->readFromQueue(Diagnostics::Topic::Simulation);
    }
    ui->lw_simulation_logs->scrollToBottom();

    std::string lastGUILog = diagnostics->readFromQueue(Diagnostics::Topic::Gui);
    while (lastGUILog != "")
    {
        ui->lw_GUI_logs->addItem(QString::fromStdString(lastGUILog));
        lastGUILog = diagnostics->readFromQueue(Diagnostics::Topic::Gui);
    }
    ui->lw_GUI_logs->scrollToBottom();

    std::string lastViewerLog = diagnostics->readFromQueue(Diagnostics::Topic::Viewer);
    while (lastViewerLog != "")
    {
        ui->lw_viewer_logs->addItem(QString::fromStdString(lastViewerLog));
        lastViewerLog = diagnostics->readFromQueue(Diagnostics::Topic::Viewer);
    }
    ui->lw_viewer_logs->scrollToBottom();

}


void DiagnosticsWindow::displayNew(Diagnostics::Topic topic, std::string log) {
    switch (topic)
    {
    case Diagnostics::Topic::Simulation:
        break;
    case Diagnostics::Topic::Gui:
        //ui->lw_gui_logs.addItem(QString::fromStdString(log));
        break;
    case Diagnostics::Topic::Viewer:
        //ui->lw_viewer_logs.addItem(QString::fromStdString(log));
        break;
    default:
        break;
    }
}

/*
LogsListModel::LogsListModel(Diagnostics* diagnostics, Diagnostics::Topic topic, QObject* parent)
    : QAbstractListModel(parent), diagnostics(diagnostics), topic(topic) {};

int LogsListModel::rowCount(const QModelIndex& parent) const {
    return diagnostics->getLogsNumber(topic);
};

QVariant LogsListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();
    std::cout << "row: " << index.row() << "; col: " << index.column() << "; role : " << role << ";" << std::endl;

    std::string element = diagnostics->readLog(topic, index.row());

    if (element == "")
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QVariant(QString::fromStdString(element));
    }
    else {
        return QVariant();
    }
};

*/