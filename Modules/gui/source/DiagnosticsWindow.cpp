#include "DiagnosticsWindow.h"
#include "ui_DiagnosticsWindow.h"


DiagnosticsWindow::DiagnosticsWindow(Diagnostics* diagnostics, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DiagnosticsWindow),
    diagnostics(diagnostics)
{
    ui->setupUi(this);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&DiagnosticsWindow::updateLogs));
    timer->start(20);
}

DiagnosticsWindow::~DiagnosticsWindow()
{
    delete ui;
}

void DiagnosticsWindow::updateLogs() {
    std::string lastGUILog = diagnostics->getLogString(Diagnostics::Topic::Gui);
    if (lastGUILog != "") {
        ui->te_gui_logs->append(QString::fromStdString(lastGUILog));
        if (ui->cb_autoscroll_GUI->isChecked()) {
            ui->te_gui_logs->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
            ui->te_gui_logs->ensureCursorVisible();
        }
    }

    std::string lastSimulationLog = diagnostics->getLogString(Diagnostics::Topic::Simulation);
    if (lastSimulationLog != "") {
        ui->te_simulation_logs->append(QString::fromStdString(lastSimulationLog));
        if (ui->cb_autoscroll_simulation->isChecked()) {
            ui->te_simulation_logs->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
            ui->te_simulation_logs->ensureCursorVisible();
        }
    }

    std::string lastViewerLog = diagnostics->getLogString(Diagnostics::Topic::Viewer);
    if (lastViewerLog != "") {
        ui->te_viewer_logs->append(QString::fromStdString(lastViewerLog));
        if (ui->cb_autoscroll_viewer->isChecked()) {
            ui->te_viewer_logs->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
            ui->te_viewer_logs->ensureCursorVisible();
        }
    }

    std::string monitor = diagnostics->getMonitorString();
    ui->te_monitor->setText(QString::fromStdString(monitor));
    ui->te_monitor->ensureCursorVisible();
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