#include "server_config.h"
#include "ui_server_config.h"

server_config::server_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server_config)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
}

server_config::~server_config()
{
    delete ui;
}

void server_config::find_script(){
    ui->plainTextEdit->clear();
    QString path = R"(D:\server\serverdata\server.cfg)";
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data = file.readAll();
        file.close();
        QRegExp key_type("ensure \\w+\\r\\n");
        mat_pos = 0;
        while((mat_pos = key_type.indexIn(data, mat_pos)) != -1){
            QStringList list = key_type.capturedTexts();
            foreach (QString string, list) {
                ui->plainTextEdit->appendPlainText(string);
            }

            mat_pos += key_type.matchedLength();
            last_script_pos = mat_pos;
        }
    }
}

void server_config::add_script(QString name){
    QString path = R"(D:\server\serverdata\server.cfg)";
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray content = file.readAll();
        file.close();
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            content.insert(last_script_pos, "ensure test\r\n");
            file.write(content);
            file.close();
        }
    }
}
