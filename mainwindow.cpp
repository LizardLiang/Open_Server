#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("FiveM 遠端開關程式");
    connect(this, SIGNAL(add_log(QString)), m_log, SLOT(add_log(QString)));
    tcp_server_on();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tcp_server_on(){
    m_server = new QTcpServer();

    m_server->listen(QHostAddress::Any, 19999);
    QString msg_log = nullptr;
    if(m_server->isListening()){
        msg_log = QString("伺服器已啟動");
    }
    else{
        msg_log = QString("無法啟動伺服器");
    }
    emit add_log(msg_log);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void MainWindow::newConnection(){

    rec_socket = m_server->nextPendingConnection();

    connect(rec_socket, &QTcpSocket::readyRead, this, &MainWindow::read_message);
}

void MainWindow::read_message(){
    rec_socket = static_cast<QTcpSocket*>(QObject::sender());

    QString msg = rec_socket->readAll().data();

    if(msg == "Open_Server")
        open_server();
    else if(msg == "Close_Server"){
        close_server();
    }

    QString msg_log = QString("Get msg - %1").arg(msg);
    emit add_log(msg_log);
}

void MainWindow::open_server(){
    QString path = m_path->getpath();
    m_config->find_script();
    m_config->show();
    if(path == nullptr)
        path = R"(E:\server1\run.bat)";
//    process->setWorkingDirectory(R"(E:\server\serverdata)");
    process = new QProcess();
    process->start("cmd.exe", QStringList() << "/c" << R"(E:\server1\run.bat)");
    QString msg_log = QString("Process error - %1").arg(process->errorString());
    emit add_log(msg_log);
    connect(process, &QProcess::readyReadStandardOutput,
            [=](){
        QString msg_send_1 = QString::fromUtf8(process->readAllStandardOutput());
        ui->plainTextEdit->appendPlainText(msg_send_1);
        emit add_log(msg_send_1);
        if(rec_socket != nullptr){
            rec_socket->write(msg_send_1.toStdString().data());
        }
    });
    if(rec_socket != nullptr){
        QString msg_send = "伺服器已開啟\n";
        rec_socket->write(msg_send.toStdString().data());
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString address = m_address->getaddress();

    m_socket = new QTcpSocket();
    if(address == nullptr)
        address = "114.32.157.74";
    m_socket->connectToHost(address, 19999);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(read_msg()));
    if(m_socket->isOpen()){
        is_connect = true;
        QString msg_screen;
        msg_screen = QString("已成功連線至主機 - %1:%2\n").arg(address).arg("19999");
        ui->plainTextEdit->appendPlainText(msg_screen);
    }
    else
        ui->plainTextEdit->appendPlainText("無法連線至主機\n");
}

void MainWindow::on_fivem_start_clicked()
{
    ui->plainTextEdit->clear();
    QString path = m_path->getpath();
    if(path == nullptr)
        path = R"(E:\server1\run.bat)";
    QString msg_screen = QString("伺服器資料位置 - %1\n").arg(path);
    ui->plainTextEdit->appendPlainText(msg_screen);
    QFile file(path);
    if(not file.exists()){
        msg_screen = QString("伺服器資料不存在\n");
        ui->plainTextEdit->appendPlainText(msg_screen);
        if(is_connect)
            m_socket->write("Open_Server");
        else{
            ui->plainTextEdit->appendPlainText("請先進行連線再點擊開服\n");
            return;
        }
    }
    else{
        open_server();
    }
}

void MainWindow::close_server(){
    //QString msg_log = QString("伺服器目前狀態 - %1").arg(process->isOpen());
    //m_log->add_log(msg_log);
    //如果有找到pid代表現在伺服器是上線狀態
    if(process->isOpen()){
        process->kill();
        process->waitForFinished();
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("伺服器已關閉\n");
        QString msg_send = "伺服器已關閉\n";
        if(rec_socket != nullptr){
            if(rec_socket->isOpen()){
                rec_socket->write(msg_send.toStdString().data());
            }
        }
        QString msg_log = QString("伺服器目前狀態 - %1").arg(process->isOpen());
        emit add_log(msg_log);
    }
    else{
        if(is_connect)
            m_socket->write("Close_Server");
        else{
            on_pushButton_clicked();
            if(is_connect)
                m_socket->write("Close_Server");
        }
    }

}

void MainWindow::read_msg(){
    QString msg = m_socket->readAll().data();
    ui->plainTextEdit->appendPlainText(msg);
}

void MainWindow::on_fivem_close_clicked()
{
    close_server();
}

void MainWindow::on_address__clicked()
{
    m_address->show();
    m_address->raise();
}

void MainWindow::on_path__clicked()
{
    m_path->show();
    m_path->raise();
}
