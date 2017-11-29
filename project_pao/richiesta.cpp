#include "richiesta.h"

richiesta::richiesta()
{}

richiesta::richiesta(QString is, QString bn,QDate s, QDate e, QString u )
    : fumettoID(is), fumettoName(bn), sdate(s), eDate(e), userID(u){
}
QString richiesta::getFumettoID()const{return fumettoID;}
QString richiesta::getFumettoName()const{return fumettoName;}
QDate richiesta::getEDATE()const{return eDate;}
QDate richiesta::getSDATE()const{return sdate;}
QString richiesta::getUser()const{return userID;}
