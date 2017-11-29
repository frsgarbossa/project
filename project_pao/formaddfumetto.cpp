#include "formaddfumetto.h"
#include "ui_formaddfumetto.h"
#include <QPixmap>
#include <QFileDialog>
#include <manga.h>
#include <QMessageBox>
#include <QRegExp>

formaddfumetto::formaddfumetto(QWidget *parent=0, fumettomodelviewtable * model=0) :
    QDialog(parent),
    ui(new Ui::formaddfumetto),mod(model)
{
    ui->setupUi(this);
}


formaddfumetto::~formaddfumetto()
{
    delete ui;
}

void formaddfumetto::on_loadFile_clicked()
{
    QString file= QFileDialog::getOpenFileName(this, "Choise a cover for your fumetto!", ":/",("Images (*.png *.jpg)"));
    QPixmap img(file);
    ui->lineIMGpath->setText(file);
    ui->coverLabel->setScaledContents( true );
    ui->coverLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->coverLabel->setPixmap(img);
}

void formaddfumetto::on_addNewButton_clicked()
{
    QRegExp re("^[0-9]+$");
    QRegExpValidator *v = new QRegExpValidator(re);
    ui->isbnLine->setValidator(v);
    if(!ui->isbnLine->hasAcceptableInput() || ui->nameEdit->text().isEmpty() || ui->authorLine->text().isEmpty() || ui->subLine->text().isEmpty()){
        QMessageBox e;
        e.warning(this, "Dati non validi", "Codice deve essere un numero! Nome fumetto,autore e cod sono obbligatori!");
        return;
    }
    else{
        QString cover, desc, sub;
        cover=ui->lineIMGpath->text();
        desc=ui->descText->toPlainText();
        sub=ui->subLine->text();
        if(ui->lineIMGpath->text().isEmpty()){
            cover="nessuna";
        }
        if(ui->descText->toPlainText().isEmpty()){
            desc="nessuna";
        }
        if(ui->subLine->text().isEmpty()){
            sub="nessuno";
        }
        if(mod->addFumetto(ui->comboType->currentText(),ui->isbnLine->text(),cover,ui->nameEdit->text(),ui->authorLine->text(),desc, sub,ui->dateEdit->date() )){
            QMessageBox i;
            i.information(this, "Inserimento", "fumetto inserito corretamente!");
        }
        else{
            QMessageBox er;
            er.critical(this,"Inserimento", "Errore durante l'inserimento! Impossibile inserire il fumetto!");
        }
    }
    this->close();
}

void formaddfumetto::on_addCancelButton_clicked()
{
    this->close();
}
