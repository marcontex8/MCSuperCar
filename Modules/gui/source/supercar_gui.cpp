#include "supercar_gui.h"
#include "./ui_supercar_gui.h"

SuperCarMain_GUI::SuperCarMain_GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SuperCarMain_GUI)
{
    ui->setupUi(this);
}

SuperCarMain_GUI::~SuperCarMain_GUI()
{
    delete ui;
}

