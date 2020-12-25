#include "supercar_gui.h"
#include "./ui_supercar_gui.h"

SuperCar_GUI::SuperCar_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SuperCar_GUI)
{
    ui->setupUi(this);
}

SuperCar_GUI::~SuperCar_GUI()
{
    delete ui;
}

