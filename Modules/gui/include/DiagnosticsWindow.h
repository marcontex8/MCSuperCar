#ifndef SUPERCAR_DIAGNOSTICSWINDOW_H
#define SUPERCAR_DIAGNOSTICSWINDOW_H

#include <QtWidgets>

#include "Diagnostics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DiagnosticsWindow; }
QT_END_NAMESPACE

class DiagnosticsWindow : public QWidget
{
    Q_OBJECT

public:
    DiagnosticsWindow(Diagnostics* diagnostics, QWidget* parent = nullptr);
    ~DiagnosticsWindow();
private:
    Ui::DiagnosticsWindow* ui;

    Diagnostics* diagnostics;

    void updateLogs();

private slots:
};
#endif // SUPERCAR_DIAGNOSTICSWINDOW_H
