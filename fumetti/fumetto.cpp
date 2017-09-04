#include "fumetto.h"

//metodi della classe fumetto
fumetto::fumetto(){}
fumetto::fumetto(QString i, QString n, QString a, QString c, QDate d, QString ds)
    :cover(i), nome(n), autore(a), cod(c), date(d), desc(ds) {}
QString fumetto::getAutore() const{return autore;}
QString fumetto::getCover() const{return cover;}
QString fumetto::getNome() const{return nome;}
QString fumetto::getCod() const{return cod;}
QDate fumetto::getDate() const{return date;}
QString fumetto::getDesc() const{return desc;}

//double fumetto::getPrezzo() const{return prezzo;}
