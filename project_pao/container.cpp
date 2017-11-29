#include "container.h"
#include <manga.h>
#include <comicbook.h>
#include <QDebug>
#include <QMessageBox>

container::container()
    :first(0), last(0){}

container::node::node(fumetto* i, node* p, node* n, int x) //costruttore del nodo
    :info(i), prev(p), next(n), nc(x) {}

void container::DeepDelete(node* p) {
    if(p){
        DeepDelete(p->next);
        delete p;
    }
}

container::node* container::DeepCopy(node* n) {
    if(!n) return 0;
    node* t = new node(n->info,0,0, n->nc);
    node* p = t;
    while(n->next) {
        p->next = new node(n->next->info,p,0,n->next->nc);
        p = p->next;
        n = n->next;
    }
    return t;
}

container::node* container::GetLast(node* n) {
    if(!n) return 0;
    while(n->next) n = n->next;
    return n;
}

container::container(const container& l): first(DeepCopy(l.first)), last(GetLast(first)) {}

container::~container() {DeepDelete(first);}

container& container::operator=(const container& l) {
    if(this != &l) {
        node* temp = first;
        first = DeepCopy(l.first);
        last = GetLast(first);
        DeepDelete(temp);
    }
    return *this;
}

bool container::iterator::operator==(const iterator& it) const {
    return punt == it.punt;
}

bool container::iterator::operator!=(const iterator& it) const {
    return punt != it.punt;
}

container::iterator& container::iterator::operator++() {
    if(punt) punt = punt->next;
    return *this;
}

container::iterator container::iterator::operator++(int) {
    iterator aux = *this;
    if(punt) punt = punt->next;
    return aux;
}

container::iterator& container::iterator::operator--() {
    if(punt) punt = punt->prev;
    return *this;
}

container::iterator container::iterator::operator--(int) {
    iterator aux = *this;
    if(punt) punt = punt->prev;
    return aux;
}

container::iterator container::begin() const {
    iterator aux;
    aux.punt = first;
    return aux;
}

container::iterator container::end() const {
    iterator aux;
    aux.punt = 0;
    return aux;
}

fumetto* container::operator[](const iterator& it)const {
    return (it.punt)->info;
}

void container::addFumetto(fumetto* b, unsigned int x = 1){
    bool found=false;
    for(container::iterator it = this->begin(); it != this->end(); it++) {
        if(it.punt->info->getCod() == b->getCod() && !found) {
            found = true;
            it.punt->nc++;
        }
    }
    if(!found){
        if(last) {
            last = new node(b,last,0, x);
            (last->prev)->next = last;
        }
        else
            first = last = new node(b,0,0,x);
    }
}

fumetto* container::operator[](unsigned int a) const {
    fumetto* copy;
    unsigned int x = 0;
    bool found = false;
    for(container::iterator it = this->begin(); it != this->end(); it++) {
        if(x == a && !found) {
            copy = (*this)[it];
            found = true;
        }
        x++;
    }
    if(found) return copy;
    else return 0;
}
bool container::removeAllCopies(QString& is) {
    node* n = first;
    node* p = 0;
    while(n && n->info->getCod() != is) {
        p = n;
        n = n->next;
    }
    if(n) {
        if(!p) {
            first = n->next;
            if(n->next) n->next->prev = 0;
        }
        else if(n->next) {
                p->next = n->next;
                n->next->prev = p;
        }
        else {
                p->next = 0;
                last = p;
        }
        delete n;
    }
    else
        return false;
    return true;
}

unsigned int container::size() const {
    if(!first) return 0;
    unsigned int size = 1;
    node* n = first;
    while(n->next) {
        size++;
        n = n->next;
    }
    return size;
}

int container::getCN(const fumetto* p) const{
    for(container::iterator it = this->begin(); it != this->end(); it++) {
        if(p->getCod() == it.punt->info->getCod()) {
            return it.punt->nc;
        }
    }
    return 0;
}

void container::incCN(const fumetto* b){
    for(container::iterator it = this->begin(); it != this->end(); it++) {
        if(b->getCod()== (*this)[it]->getCod()) {
            it.punt->nc++;
            return;
        }
    }
}
void container::decCN(const fumetto *b){
    for(container::iterator it = this->begin(); it != this->end(); it++) {
        if(b->getCod()== (*this)[it]->getCod()) {
            if(it.punt->nc>0)
                it.punt->nc--;
            return;
        }
    }

}
