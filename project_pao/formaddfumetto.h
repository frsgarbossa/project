#ifndef FORMADDFUMETTO_H
#define FORMADDFUMETTO_H

#include <QDialog>
#include "fumettomodelviewtable.h"

namespace Ui{
class formaddfumetto;
}
class formaddfumetto: public QDialog
{
    Q_OBJECT

public:
    formaddfumetto(QWidget *parent, fumettomodelviewtable *);
    ~formaddfumetto();

private slots:
    void on_loadFile_clicked();

    void on_addNewButton_clicked();

    void on_addCancelButton_clicked();

private:
    Ui::formaddfumetto *ui;
    fumettomodelviewtable *mod;
};


#endif // FORMADDFUMETTO_H
