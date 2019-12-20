#include "server_config.h"
#include "ui_server_config.h"

server_config::server_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_config)
{
    ui->setupUi(this);
}

server_config::~server_config()
{
    delete ui;
}

void server_config::find_script(){
}
