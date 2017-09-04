#ifndef FUMETTO_H
#define FUMETTO_H

#include <QString>
#include <QDate>
#include <QPixmap>

class fumetto
{
private:
    QString cover;//immagine di copertina
    QString nome;//nome
    QString autore;//autore
    QString cod;//codice che identifica il fumetto univocamente
    QDate date;//data pubblicazione
    QString desc;//descrizione prodotto
    //double prezzo;//prezzo articolo
public:
    fumetto();
    fumetto(QString, QString, QString, QString, QDate, QString);
    virtual fumetto* clone() const=0;//metodo per la clonazione
    inline virtual ~fumetto() {}   //distruttore virtuale
    virtual QString getSubject() const=0;

    QString getCover() const;
    QString getNome() const;//restituisce il nome del prodotto
    QString getAutore() const;//autore
    QString getCod() const;//codice
    QDate getDate() const;//la data
    QString getDesc() const;//descrizione
    //double getPrezzo() const;//prezzo
};

#endif // FUMETTO_H
