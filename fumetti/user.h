#ifndef USER_H
#define USER_H
#include<QString>
#include<QDate>
class user
{
private:
    QString name;//nome
    QString sname;//cognome
    QDate dob;//data di nascita
    QString username; //chiave primaria, non possono essere piu di 1 utente con lo stesso nome
    QString password;
public:
    user();
    user(QString, QString, QDate, QString, QString);
    virtual QString getType()const=0;
    virtual ~user();
    QString getName()const;
    QString getSname()const;
    QDate getDate()const;
    QString getUname()const;
    QString getPassword()const;
};

#endif // USER_H
