#include "formuserinfo.h"
#include "ui_formuserinfo.h"
#include "user.h"
#include <QDate>
#include <QString>

FormUserInfo::FormUserInfo(QWidget *parent, user*user) :
    QDialog(parent),
    ui(new Ui::FormUserInfo), me(user)
{
    ui->setupUi(this);
    QString name=me->getName();
    QString sname=me->getSname();
    QString us=me->getUname();
    QDate bd=me->getDate();
    ui->nameLabel->setText(name);
    ui->snameLabel->setText(sname);
    ui->dbLabel->setText(bd.toString());
    ui->unLabel->setText(us);
}

FormUserInfo::~FormUserInfo()
{
    delete ui;
}

void FormUserInfo::on_okButton_clicked()
{
    this->close();
}

