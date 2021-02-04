#ifndef SUPERCAR_DIAGNOSTICSWINDOW_H
#define SUPERCAR_DIAGNOSTICSWINDOW_H

#include <QtWidgets>

#include "Diagnostics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DiagnosticsWindow; }
QT_END_NAMESPACE

/*
class LogsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    LogsListModel(Diagnostics* diagnostics, Diagnostics::Topic topic, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    //QVariant headerData(int section, Qt::Orientation orientation,
    //    int role = Qt::DisplayRole) const override;

    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    //Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    Diagnostics* diagnostics;
    Diagnostics::Topic topic;

signals:
    void editCompleted(const QString&);
};
*/


class DiagnosticsWindow : public QWidget
{
    Q_OBJECT

public:
    DiagnosticsWindow(Diagnostics* diagnostics, QWidget* parent = nullptr);
    ~DiagnosticsWindow();

    void displayNew(Diagnostics::Topic topic, std::string log);

private:
    Ui::DiagnosticsWindow* ui;

    Diagnostics* diagnostics;

    void updateLogs();


    //LogsListModel* guiLogsListModel = nullptr;
    //LogsListModel* simulatorLogsListModel = nullptr;
    //LogsListModel* viewerLogsListModel = nullptr;

private slots:
};
#endif // SUPERCAR_DIAGNOSTICSWINDOW_H
