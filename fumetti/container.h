#ifndef CONTAINER_H
#define CONTAINER_H
#include <vector>
#include "fumetto.h"
#include <QFile>
#include <QXmlStreamReader>

using std::vector;
//contenitore che contiene i puntatori alle pubblicazioni ed un intero che serve per specificare il numero di copie di quell'oggetto
class container
{   friend class iterator;
private:
    class node{//solita classe nodo
    public:
        fumetto* info;
        node* prev;
        node* next;
        int nc; //numero di copie per ogni fumetto, motivo per il quale ho creata questo contenitore.
        node(fumetto*, node*, node*, int);
    };
    node* first;//puntatore al primo elemento
    node* last;//puntatore al ultimo elemento

    //COPIA PROFONDA
    static node* DeepCopy(node*);
    static node* GetLast(node*);
    static void DeepDelete(node*);
public:
    class iterator{
        friend class container;
    private:
        container::node* punt;
    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
    };

    container();

    //COPIA PROFONDA
    container(const container&);//COSTRUTORE DI COPIA PROFONDO
    ~container();//DISTRUTTORE PROFONDO
    container& operator=(const container&);//ASSEGNAZIONE PROFONDO


   //ALTRI METODI CLASSICI
    container::iterator begin() const;
    container::iterator end() const;
    void addFumetto(fumetto*, unsigned int);
    bool removeAllCopies(QString&);//riceve il codice del fumetto e rimuove tutte le copie del fumetto con quel codice
    fumetto* operator[](const iterator& )const;
    fumetto* operator[](unsigned int) const;
    unsigned int size() const;//restituisce la dimensione del contenitore

    //METODI PER MODIFICARE O LEGGERE L INTERO CHE CONTIENE IL NUMERO DI COPIE - motivo per il quale e' stato implementato questo contenitore
    int getCN(const fumetto*)const;//restitusce il numero di copie per un dato fumetto
    void incCN(const fumetto*);//metodo per incrementare
    void decCN(const fumetto*);//metodo per deincrementare
    };


#endif // CONTAINER_H
