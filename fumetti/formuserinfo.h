#ifndef FORMUSERINFO_H
#define FORMUSERINFO_H

#include <QDialog>
#include "user.h"

namespace Ui {
class FormUserInfo;
}

class FormUserInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FormUserInfo(QWidget *parent = 0, user * user=0);
    ~FormUserInfo();

private slots:
    void on_okButton_clicked();


private:
    Ui::FormUserInfo *ui;
    user *me;
};

#endif // FORMUSERINFO_H
