#ifndef ADMINUSER_H
#define ADMINUSER_H
#include"user.h"
#include <QString>

class adminuser:public user
{
private:
    static QString type;
public:
    adminuser();
    adminuser(QString, QString, QDate,QString, QString);
    QString getType()const;
};


#endif // ADMINUSER_H
