#include "comicbook.h"

comicbook::comicbook(){}
comicbook::comicbook(QString i, QString n, QString a, QString c, QDate d, QString ds, QString s)
    :fumetto(i, n, a, c, d, ds), superhero(s){}
comicbook* comicbook::clone() const{return new comicbook(*this);}
QString comicbook::getSubject()const{return superhero;}

