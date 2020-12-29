#ifndef SUPERCAR_GUI_H
#define SUPERCAR_GUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SuperCarMain_GUI; }
QT_END_NAMESPACE

class SuperCarMain_GUI : public QMainWindow
{
    Q_OBJECT

public:
    SuperCarMain_GUI(QWidget *parent = nullptr);
    ~SuperCarMain_GUI();

private:
    Ui::SuperCarMain_GUI*ui;
};
#endif // SUPERCAR_GUI_H
