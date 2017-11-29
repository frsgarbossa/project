#include "manga.h"

manga::manga(){}
manga::manga(QString i, QString n, QString a, QString c, QDate d, QString ds, QString g)
    : fumetto(i, n, a, c, d, ds), genere(g){}
manga* manga::clone() const{return new manga(*this);}
QString manga::getSubject()const{return genere;}
