#ifndef RICHIESTA_H
#define RICHIESTA_H
#include <QString>
#include <QDate>


//un oggetto di questa classe rapressenta un prestito
class richiesta
{
private:
    QString fumettoID;//CODICE FUMETTO
    QString fumettoName;//NOME FUMETTO
    QDate sdate;//DATA INIZIO
    QDate eDate;//DATA FINE
    QString userID; //NOME UTENTE
public:
    richiesta();
    richiesta(QString, QString,QDate, QDate, QString);
    QDate getSDATE()const;
    QDate getEDATE()const;
    QString getFumettoID()const;
    QString getFumettoName()const;
    QString getUser()const;
};


#endif // RICHIESTA_H
