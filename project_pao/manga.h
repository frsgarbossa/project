#ifndef MANGA_H
#define MANGA_H
#include "fumetto.h"
#include <QString>
#include <QDate>


class manga: public fumetto
{
private:
    QString genere;
public:
    manga();
    manga(QString, QString, QString, QString, QDate, QString, QString);
    manga* clone()const;
    QString getSubject() const;
};

#endif // MANGA_H
