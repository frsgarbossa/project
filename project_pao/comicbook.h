#ifndef COMICBOOK_H
#define COMICBOOK_H
#include "fumetto.h"
#include <QString>
#include <QDate>

class comicbook: public fumetto
{
private:
    QString superhero;
public:
    comicbook();
    comicbook(QString, QString, QString, QString, QDate, QString, QString);
    comicbook* clone()const;
    QString getSubject() const;
};

#endif // COMICBOOK_H
