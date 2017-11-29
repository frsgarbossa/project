#ifndef FORMADDUSER_H
#define FORMADDUSER_H

#include "usermodelview.h"
#include <QDialog>

namespace Ui {
class formadduser;
}

class formadduser : public QDialog
{
    Q_OBJECT

public:
    explicit formadduser(QWidget *parent, usermodelview *);
    ~formadduser();

private slots:
    void on_addUserCancel_clicked();

    void on_addUser_clicked();

private:
    Ui::formadduser *ui;
    usermodelview* mod;
};

#endif // FORMADDUSER_H
