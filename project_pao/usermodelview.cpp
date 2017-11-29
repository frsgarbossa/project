#include "usermodelview.h"
#include "adminuser.h"
#include "normaluser.h"
#include <QMessageBox>
#include "normaluser.h"
#include "admin.h"

usermodelview::usermodelview()
{
}


/***METODI VITUALI DERIVATI DALLA SUPER CLASSE***/

//IL METODO RESTITUISCE IL NUMERO DI RIGHE DELLA TABELLA
int usermodelview::rowCount(const QModelIndex& parent) const
{
  return v.size();
}

//METODO RESTITUISCE IL NUMERO DI COLONNE DELLA TABELLA
int usermodelview::columnCount(const QModelIndex& parent) const
{
  return 4;
}

//METODO SERVE PER CARICARE DATI NEL MODELLO(TABELLA IN QUESTO CASO)
QVariant usermodelview::data(const QModelIndex& index, int role) const
{
    int row=index.row();//righe
    int col=index.column();//colonne
    if(role == Qt::DisplayRole)
    {
            user *c=v.operator [](row);//carico un prestito base alla riga, ovviamente la riga non superaara mai la dimenzione del vettore v
            if(col==0)
                return c->getUname();//se è la prima colonna restituisco isbn
            if(col==1)
                return c->getName();//seconda colonna nome libro
            if(col==2)
                return c->getSname();//data inizio prestito
            if(col==3)
                return c->getDate();//data fine prestito

    }
    return QVariant::Invalid;

}

//SERVE PER HEADER DELLA TABELLA(OVVERO I NOME DELLE VARIE COLONNE). IN QUESTO CASO 4 COLONNE
QVariant usermodelview::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("UTENTE");
            case 1:
                return QString("NOME");
            case 2:
                return QString("COGNOME");
            case 3:
                return QString("DATA DI NASCITA");
            }
        }
    }
    return QVariant();
}


 bool usermodelview::addUser(QString type, QString n, QString sn, QString un, QString pass, QDate bd){
         if(type=="Utente admin"){
             beginInsertRows( QModelIndex(),this->rowCount(QModelIndex())-1, this->rowCount(QModelIndex())-1); //notify views and proxy models that a line will be inserted
                 v.push_back(new adminuser(n, sn, bd, un, pass));
             endInsertRows();
             return true;
         }
         if(type=="Utente normale"){
             beginInsertRows( QModelIndex(),this->rowCount(QModelIndex())-1, this->rowCount(QModelIndex())-1); //notify views and proxy models that a line will be inserted
                 v.push_back(new normaluser(n, sn, bd, un, pass));
             endInsertRows();
             return true;
         }
     return false;
 }

 bool usermodelview::removeUser(QString un){
     bool cond=false;
     int row=0;
     for(unsigned int i=0; i<v.size() && !cond; i++){

         user* temp=v.operator [](i);
         if(temp->getUname()==un){

             cond=true;
         }else{
             row++;
         }
     }

     beginRemoveRows(QModelIndex(), row, row );
         v.erase(v.begin()+row);
     endRemoveRows();
     if(cond){
         return true;
     }
     return false;
 }

user* usermodelview::find(QString un) const{
    for(unsigned int i =0;i<v.size(); i++){
        user* temp= v.operator [](i);
        if(temp->getUname()==un){
            return temp;
        }
    }
    return 0;
}


//METODI PER CARICARE I DATI DAI FILE XML
//RICEVE UN QFILE E UNA STRINGA(nome utente), CARICA TUTTI I PRESTTI DI QUEL UTENTE DAL FILE XML.
void usermodelview::loadUser(QFile& f){
    if(!f.open(QFile::Text|QFile::ReadOnly)){
          QMessageBox err;
          err.critical(0,"Opning", "File xml does not found!");
     }else{
          QXmlStreamReader file(&f);
          if (file.readNextStartElement()) {
                   if (file.name() == "users"){
                       while(file.readNextStartElement()){
                           if(file.name() == "user"){
                               this->loadSingleUser(file);
                           }
                           else{
                               file.skipCurrentElement();
                           }
                       }
                   }
                   else{
                       QMessageBox err2;
                       err2.critical(0, "Wrong file","File xml is not a valid file. Please try with another file!");
                   }
               }
          file.clear();
          f.close();
    }
}
void usermodelview::loadSingleUser(QXmlStreamReader &file){
    QString uname,pass, name, sname,type, y, m , d;
    bool cond=false;
    type=file.attributes().value("type").toString();
    while(file.readNextStartElement() && !cond){
        if(file.name() == "uname"){
                uname = file.readElementText();
         }
        if(file.name() == "password"){
                pass = file.readElementText();
         }
        if(file.name() == "name"){
                 name = file.readElementText();
         }
         if(file.name() == "sname"){
                 sname = file.readElementText();
         }
         if(file.name()=="b_date"){
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
             cond=true;
         }


     }

    QDate p(y.toInt(), m.toInt(), d.toInt());

    if(type=="admin"){
         v.push_back(new adminuser(name, sname, p, uname, pass));
    }
    if(type=="user"){
         v.push_back(new normaluser(name, sname, p, uname, pass));
    }
}


bool usermodelview::saveData(QFile& file)const
{
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox err;
            err.critical(0," Errore apertura", "Nessun file XML trovato!");
            return false;
        }
            QXmlStreamWriter *writer = new QXmlStreamWriter();
            writer->setDevice(&file);
            writer->writeStartDocument();
            writer->writeStartElement("users");
            for (unsigned int i=0; i < v.size(); i++)
            {   QString type;
                user *b = dynamic_cast<normaluser*>(v.operator [](i));
                if (b)
                {
                    type="user";
                }
                 else{
                    b=dynamic_cast<adminuser*>(v.operator [](i));
                    type="admin";
                }
                    writer->writeStartElement("user");
                    writer->writeAttribute("type", type);
                    writer->writeTextElement("uname",b->getUname());
                    writer->writeTextElement("password",b->getPassword());
                    writer->writeTextElement("name",b->getName());
                    writer->writeTextElement("sname",b->getSname());
                    writer->writeStartElement("b_date");
                        writer->writeTextElement("year",QString::number(b->getDate().year()));
                        writer->writeTextElement("month",QString::number(b->getDate().month()));
                        writer->writeTextElement("day", QString::number(b->getDate().day()));
                    writer->writeEndElement();
                    writer->writeEndElement();
            }
            writer->writeEndElement();
            writer->writeEndDocument();
            delete writer;
            return true;
}

