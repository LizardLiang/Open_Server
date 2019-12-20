#ifndef MAIN_ADDRESS_H
#define MAIN_ADDRESS_H

#include <QDialog>

namespace Ui {
class main_address;
}

class main_address : public QDialog
{
    Q_OBJECT

public:
    explicit main_address(QWidget *parent = nullptr);
    ~main_address();

    QString getaddress();

private:
    Ui::main_address *ui;
};

#endif // MAIN_ADDRESS_H
