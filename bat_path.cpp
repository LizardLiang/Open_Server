#include "bat_path.h"
#include "ui_bat_path.h"

bat_path::bat_path(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bat_path)
{
    ui->setupUi(this);
}

bat_path::~bat_path()
{
    delete ui;
}

QString bat_path::getpath(){
    return ui->lineEdit->text();
}
