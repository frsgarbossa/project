#include "user.h"

user::user()
{}
user::user(QString n, QString sn, QDate d, QString un, QString p)
    :name(n), sname(sn), dob(d), username(un), password(p){}
user::~user(){}
QDate user::getDate()const{return dob;}
QString user::getName()const{return name;}
QString user::getSname()const{return sname;}
QString user::getUname()const{return username;}
QString user::getPassword()const{return password;}
