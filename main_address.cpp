#include "main_address.h"
#include "ui_main_address.h"

main_address::main_address(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_address)
{
    ui->setupUi(this);
}

main_address::~main_address()
{
    delete ui;
}

QString main_address::getaddress(){
    return ui->lineEdit->text();
}
