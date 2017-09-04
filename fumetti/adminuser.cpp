#include "adminuser.h"

adminuser::adminuser(){}
adminuser::adminuser(QString n, QString sn, QDate d,QString u, QString p)
    :user(n, sn, d, u, p){}

QString adminuser::getType()const{return type;}
QString adminuser::type="admin";
