#ifndef BAT_PATH_H
#define BAT_PATH_H

#include <QDialog>

namespace Ui {
class bat_path;
}

class bat_path : public QDialog
{
    Q_OBJECT

public:
    explicit bat_path(QWidget *parent = nullptr);
    ~bat_path();

    QString getpath();

private:
    Ui::bat_path *ui;
};

#endif // BAT_PATH_H
