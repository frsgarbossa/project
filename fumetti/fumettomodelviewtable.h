#ifndef FUMETTOMODELVIEWTABLE_H
#define FUMETTOMODELVIEWTABLE_H

#include <QAbstractTableModel>
#include "container.h"
#include <QString>
#include <QFile>
#include "fumetto.h"
#include "manga.h"
#include "comicbook.h"
#include <QMessageBox>

// CLASSE IMPLEMENTATA PER IL MODEL-VIEW

class fumettomodelviewtable: public QAbstractTableModel
{
public:
    fumettomodelviewtable();//costruttore senza parametri
    //metodo aggiuntivo per fornire la copertina alle views
    QString getCover(const QString)const;
    //IMPLEMENTAZIONE DEI METODI VITUALI PURI DELLA SUPER CLASSE QAbstractTableModel
    int rowCount(const QModelIndex& parent) const; //restituisce il numero di righe della tabella
    int columnCount(const QModelIndex& parent) const; //numero di colonne
    QVariant data(const QModelIndex& index, int role) const; //serve per "popolare" la tabella
    QVariant headerData(int, Qt::Orientation , int ) const; //per "settare" i nomi delle colonne(guardare il file .cpp)

    //METODO per inserire/rimuovere un (nuovo) fumetto
    bool addFumetto(QString t,QString is, QString c, QString n, QString au, QString d, QString s, QDate pd);
    bool removeFumetto(QString &);//rimuove un fumetto dal contenitore e segnale a tutte le views della rimozione

    //METODI PER CARICARE DATI DAL FILE XML NEL CONTENITORE
    void setModelContainer(QFile &);//Prende come argomento un QFile(in questo caso un file xml)e riempe il contenitore con i fumetti presenti nel file.
    void loadSingleFumetto(QXmlStreamReader&);//carica un singolo fumetto...utilizzato per implementare il metodo sopra

    //METODO PER AGGIORNARE IL FILE XML(DATABASE)
    bool saveData(QFile &)const;


    //METODI PER RIMUOVERE E AGGIUNGERE UNA COPIA SOLA
    void addCopy(QString);
    void removeCopy(QString);
private:
    container a; //contenitore che contiene tutti i fumetti caricati dal file xml
};



#endif // FUMETTOMODELVIEWTABLE_H
