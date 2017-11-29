#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <fumettomodelviewtable.h>
#include <richiestamodelview.h>
#include <QAbstractProxyModel>
#include <QSortFilterProxyModel>
#include <QCloseEvent>
#include <QFile>
#include <QRegExp>
#include <QPixmap>
#include <formaddfumetto.h>
#include "user.h"
#include "usermodelview.h"
#include "formuserinfo.h"

namespace Ui{
class admin;
}
class admin:public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent=0, user* u=0, usermodelview* t=0);
    ~admin();
private slots:
    void on_searchLine_textChanged(const QString &arg1);
    void on_autoreLine_textChanged(const QString &arg1);
    void on_genereLine_textChanged(const QString &arg1);
    void on_tableView_activated(const QModelIndex &index);
    void on_tableviewuser_activated(const QModelIndex &index);
    void closeEvent(QCloseEvent *) ;
    void on_addnewB_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_deleteButton_clicked();
    void on_getFumettoButton_clicked();
    void on_returnButton_clicked();
    void on_removeUser_clicked();
    void on_tableUsersView_activated(const QModelIndex &index);
    void on_addUser_clicked();
    void on_actionExit_triggered();
    void on_actionAccount_informations_triggered();

    void on_sLineID_textChanged(const QString &arg1);

    void on_sLineName_textChanged(const QString &arg1);

    void on_sLineSname_textChanged(const QString &arg1);

private:

    //PROXY SHORT MODELS
    QSortFilterProxyModel fumettoPM;//proxy sort model per il modello Gmodel
    QSortFilterProxyModel richiestaPM;//proxy sort model per il modello userModel
    QSortFilterProxyModel usersPM;//ps per gli utenti

    //UTENTE CHE HA FATTO LOGIN
    user* loginuser;

    //MODELS
    fumettomodelviewtable Gmodel;//modello generico per tutti i fumetti da visualizzare
    richiestamodelview userModel;//modello per i prestiti del utente
    usermodelview * usersM;//puntatore per il modello che ricevo da login contenente tutti gli utenti.
    Ui::admin *ui;

};

#endif // ADMIN_H
