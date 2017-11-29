#ifndef USERMODELVIEW_H
#define USERMODELVIEW_H
#include <QAbstractTableModel>
#include <vector>
#include <QFile>
#include <QDate>
#include <QXmlStreamReader>
#include "user.h"

class usermodelview:public QAbstractTableModel
{
private:
    std::vector<user*>v;
public:
    usermodelview();

    //IMPLEMENTAZIONE DEI METODI VITUALI PURI DELLA SUPER CLASSE QAbstractTableModel -SOLO LETTURA-
    int rowCount(const QModelIndex& parent) const; //restituisce il numero di righe della tabella
    int columnCount(const QModelIndex& parent) const; //numero di colonne
    QVariant data(const QModelIndex& index, int role) const; //serve per "popolare" la tabella
    QVariant headerData(int, Qt::Orientation , int ) const; //per "setare" i nomi delle colonne(guardare il file .cpp)

    //METODO per inserire/rimuovere un (nuovo) utente
    bool addUser(QString, QString, QString, QString, QString, QDate);//sicuramente c'era un modo migliore per implementare l'inserimento di un nuovo fumetto
    bool removeUser(QString);//rimuove un utente
    user* find(QString)const;

    //METODI PER CARICARE DATI DAL FILE XML NEL CONTENITORE
    void loadUser(QFile&); //fa la stessa cosa solo che in questo caso i fumetti caricati sono di uno specidifico utente.Infatti riceve come campo dati una stringa contenente id(codice fiscale) di uno specifico utente
    void loadSingleUser(QXmlStreamReader&);//carica un singlo fumetto..usata per le due funzioni sopra

    //METODO PER AGGIORNARE IL FILE XML(DATABASE)
    bool saveData(QFile &)const;
};

#endif // USERMODELVIEW_H
