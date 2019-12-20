#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <QDialog>
#include <QFile>

namespace Ui {
class server_config;
}

class server_config : public QDialog
{
    Q_OBJECT

public:
    explicit server_config(QWidget *parent = nullptr);
    ~server_config();

    void find_script();

private:
    Ui::server_config *ui;
};

#endif // SERVER_CONFIG_H
