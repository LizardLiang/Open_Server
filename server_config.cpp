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
    QString path = R"(E:\server1\serverdata\server.cfg)";
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data = file.readAll();
        file.close();
        ui->plainTextEdit->appendPlainText(data);
        QRegExp key_type("ensure \\w+\\n");
        int num_script = key_type.indexIn(data);
//        for(int i = 0; i < num_script; i++){
//            ui->plainTextEdit->appendPlainText(key_type.cap(i));
//        }
    }
}
