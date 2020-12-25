#ifndef SUPERCAR_GUI_H
#define SUPERCAR_GUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SuperCar_GUI; }
QT_END_NAMESPACE

class SuperCar_GUI : public QMainWindow
{
    Q_OBJECT

public:
    SuperCar_GUI(QWidget *parent = nullptr);
    ~SuperCar_GUI();

private:
    Ui::SuperCar_GUI *ui;
};
#endif // SUPERCAR_GUI_H
