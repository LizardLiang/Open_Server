#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>
#include <QMessageBox>
#include <main_address.h>
#include <bat_path.h>
#include <server_config.h>

#include "D:/Famax/MotorTest/testIO/logsystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    logsystem *m_log = new logsystem;
    main_address *m_address = new main_address();
    bat_path *m_path = new bat_path();
    server_config *m_config = new server_config();

    bool is_connect = false;
    bool is_on = false;
    QProcess *process = new QProcess();

    void tcp_server_on();

    QTcpServer *m_server;           //創建一個server
    void open_server();
    void close_server();

    QTcpSocket *m_socket;
    QTcpSocket *rec_socket = nullptr;


signals:
    void add_log(QString);

private slots:
    void newConnection();

    void read_message();
    void on_pushButton_clicked();
    void on_fivem_start_clicked();
    void read_msg();
    void on_fivem_close_clicked();
    void on_address__clicked();
    void on_path__clicked();
};
#endif // MAINWINDOW_H
