#include "normaluser.h"

normaluser::normaluser()
{}
normaluser::normaluser(QString n, QString sn, QDate d,QString u, QString p)
    :user(n, sn, d, u, p){}
QString normaluser::type="normal";
QString normaluser::getType()const{return type;}
