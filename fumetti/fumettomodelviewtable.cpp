#include "fumettomodelviewtable.h"
#include "string.h"
#include "fumetto.h"
#include <QPixmap>
#include "manga.h"
#include "comicbook.h"
#include "QMessageBox"
#include <QDebug>
#include <QDate>
#include <QFileDialog>

//IMPLEMENTAZIONE DEI METODI DELLE CLASSI

//COSTRUTTORE SENZA PARAMETRI
fumettomodelviewtable::fumettomodelviewtable(){}

//SERVE PER LA COPERTINA, VISTO CHE IN TABELLA E NEL MODELLO NON VIENE CARICATA!
QString fumettomodelviewtable::getCover(const QString t) const{
    container::iterator it=a.begin();
    for(;it!=a.end();it++){
        fumetto *temp= a.operator [](it);
        if(temp->getCod()==t){
             return temp->getCover();
        }
    }
    return "";
}

//IL METODO RESTITUISCE IL NUMERO DI RIGHE DELLA TABELLA
int fumettomodelviewtable::rowCount(const QModelIndex &parent) const
{
  return a.size();
}

//METODO RESTITUISCE IL NUMERO DI COLONNE DELLA TABELLA
int fumettomodelviewtable::columnCount(const QModelIndex &parent) const
{
  return 7;
}

/***METODI VITUALI DERIVATI DALLA SUPER CLASSE***/

//METODO SERVE PER CARICARE DATI NEL MODELLO(TABELLA IN QUESTO CASO)
QVariant fumettomodelviewtable::data(const QModelIndex& index, int role) const
{
    int row=index.row();//righe
    int col=index.column();//colonne
    fumetto *c=a.operator [](row);//"pesco" il singolo fumetto dal contenitore(a) e lo faccio puntatre da c
    if(role == Qt::DisplayRole)
    {
           if(col==0)
                return c->getCod();
            if(col==1) //controllo vari casi, base alla colonna della tabella carico l 'informazione nel modello
                return c->getNome();
            if(col==2)
                return c->getAutore();
            if(col==3)
                return c->getDate();
            if(col==4)
                return c->getSubject();
            if(col==5)
                return c->getDesc();
            if(col==6)
                return a.getCN(a.operator [](row));
   }
   return QVariant::Invalid;


}

//SERVE PER HEADER DELLA TABELLA(OVVERO I NOME DELLE VARIE COLONNE)
QVariant fumettomodelviewtable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("CODICE");
            case 1:
                return QString("NOME");
            case 2:
                return QString("AUTORE");
            case 3:
                return QString("DATA PUB.");
            case 4:
                return QString("ARGOMENTO");
            case 5:
                return QString("DESCRIZIONE");
            case 6:
                return QString("COPIE DISPONIBILI");
            }
        }
    }
    return QVariant();
}


bool fumettomodelviewtable::addFumetto(QString t,QString is, QString c, QString n, QString au, QString d, QString s, QDate pd){
    bool cond=false;
    for(unsigned int i=0; i<a.size() && !cond;i++){
        fumetto *temp= a.operator [](i);
        if(temp->getCod()==is){
            //printf( " entro ");
            cond=true;
            a.addFumetto(temp, 1);
            emit dataChanged(QModelIndex(), QModelIndex());
            return true;
        }
    }
    if(!cond){
        //qDebug(t.toLatin1());
        if(t=="manga"){
            beginInsertRows( QModelIndex(),this->rowCount(QModelIndex())-1, this->rowCount(QModelIndex())-1); //notify views and proxy models that a line will be inserted
                 a.addFumetto(new manga(c, n, au, is, pd, d, s), 1);
            endInsertRows();
            return true;
        }
        if(t=="comicbook"){
            beginInsertRows( QModelIndex(),this->rowCount(QModelIndex())-1, this->rowCount(QModelIndex())-1); //notify views and proxy models that a line will be inserted
                 a.addFumetto(new comicbook(c, n, au, is, pd, d, s), 1);
            endInsertRows();
            return true;
        }
    }
    return false;
}

bool fumettomodelviewtable::removeFumetto(QString & is){//Sicuramente c'era un modo piu elegante per eliminare un fumetto
    bool cond=false;
    int row;
    for(unsigned int i=0; i<a.size()&& !cond; i++){
        row=i;
        fumetto* temp=a.operator [](i);
        if(temp->getCod()==is){
            cond=true;
        }
    }
   beginRemoveRows(QModelIndex(), row, row );
        cond=a.removeAllCopies(is);
    endRemoveRows();
    if(cond){
        return true;
    }
    return false;
}

//METODI PER LA SINGOLA COPIA
void fumettomodelviewtable::addCopy(QString is) {
    for(unsigned int i=0; i<a.size(); i++){
        fumetto* temp=a.operator [](i);
        if(temp->getCod()==is){
            a.incCN(temp);
            return;
        }
    }
}
void fumettomodelviewtable::removeCopy(QString is){
    for(unsigned int i=0; i<a.size(); i++){
        fumetto* temp=a.operator [](i);
        if(temp->getCod()==is){
            a.decCN(temp);
            return;
        }
    }
}

//METODI PER CARICARE I DATI DAI FILE XML
void fumettomodelviewtable::setModelContainer(QFile& f){

    if(!f.open(QFile::Text|QFile::ReadOnly)){
          QMessageBox err;
          err.critical(0," Errore apertura", "Nessun file XML trovato!");
     }else{
          QXmlStreamReader file(&f);
          if (file.readNextStartElement()) {
                   if (file.name() == "fumetti"){
                       while(file.readNextStartElement()){
                           if(file.name() == "fumetto"){
                               this->loadSingleFumetto(file);
                           }
                           else{
                               file.skipCurrentElement();
                           }
                       }
                   }
                   else{
                       QMessageBox err2;
                       err2.critical(0, "Errore File!","Il file selezionato non è un file xml valido!");
                   }
               }
          file.clear();
          f.close();
    }
}

void fumettomodelviewtable::loadSingleFumetto(QXmlStreamReader &file){
    QString name,cover, author, isbn, desc, sub, type, y, m , d;
    bool cond=false;
    int nc=1;
    type=file.attributes().value("type").toString();
    while(file.readNextStartElement() && !cond){
        if(file.name() == "cover"){
                cover = file.readElementText();
         }
        if(file.name() == "isbn"){
                isbn = file.readElementText();
         }
        if(file.name() == "title"){
                 name = file.readElementText();
         }
         if(file.name() == "author"){
                 author = file.readElementText();
         }
         if(file.name()=="publish_date"){
             while (file.readNextStartElement()) {
                 if(file.name() == "year"){
                         y = file.readElementText();
                 }
                 if(file.name() == "month"){
                         m = file.readElementText();
                 }
                 if(file.name() == "day"){
                         d = file.readElementText();
                  }
             }
         }
         if(file.name() == "description"){
                 desc = file.readElementText();
          }
         if(file.name() == "sub"){
                 sub = file.readElementText();
         }
         if(file.name() == "numberC"){
                 nc = file.readElementText().toInt();
                  cond=true;
         }
     }
    QDate p(y.toInt(), m.toInt(), d.toInt());

    if(type=="manga"){

        a.addFumetto(new manga(cover, name, author, isbn, p, desc, sub), nc);
    }
    if(type=="comicbook"){
         a.addFumetto(new comicbook(cover, name, author, isbn, p, desc, sub), nc);
    }
}

//METODO PER AGGIORNARE IL FILE XML

bool fumettomodelviewtable::saveData(QFile& file)const
{
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox err;
            err.critical(0," Errore apertura", "Nessun file XML trovato!");
            return false;
        }
            QXmlStreamWriter *writer = new QXmlStreamWriter();
            writer->setDevice(&file);
            writer->writeStartDocument();
            writer->writeStartElement("fumetti");
            for (unsigned int i=0; i < a.size(); i++)
            {   QString type;
                fumetto *b = dynamic_cast<manga*>(a.operator [](i));
                if (b)
                {
                    type="manga";
                }
                else{
                    b=dynamic_cast<comicbook*>(a.operator [](i));
                    type="comicbook";
                }
                    writer->writeStartElement("fumetto");
                    writer->writeAttribute("type", type);
                    writer->writeTextElement("cover",b->getCover());
                    writer->writeTextElement("isbn",b->getCod());
                    writer->writeTextElement("title",b->getNome());
                    writer->writeTextElement("author",b->getAutore());
                    writer->writeStartElement("publish_date");
                        writer->writeTextElement("year",QString::number(b->getDate().year()));
                        writer->writeTextElement("month",QString::number(b->getDate().month()));
                        writer->writeTextElement("day", QString::number(b->getDate().day()));
                    writer->writeEndElement();
                    writer->writeTextElement("description",b->getDesc());
                    writer->writeTextElement("sub",b->getSubject());
                    writer->writeTextElement("numberC",QString::number(a.getCN(b)));
                    writer->writeEndElement();
            }
            writer->writeEndElement();
            writer->writeEndDocument();
            delete writer;
            return true;
}


