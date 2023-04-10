#ifndef DLIST_H
#define DLIST_H

#include <iostream>


template <class T> class list;

template <class T> std::ostream& operator<<(std::ostream&,const list<T>&);

template <class T>
class list{
friend std::ostream& operator<< <T>(std::ostream&,const list<T>&);
//friend void Deck::sort();
friend class iterator;
private: class nodo{

                public:
                       T* info;
                       nodo *next , *prev ;
                       nodo();
                       nodo(T& i, nodo* n=0 ,nodo* p=0) ;
                       ~nodo();


    };
    nodo* first;
    nodo* last;
    unsigned int sizel;
    static void distruggi(nodo*);
public:
    class iterator{
                friend class list<T>;
                public:
                    bool operator==(iterator) const;
                    bool operator!=(iterator) const;
                    iterator& operator++();
                    iterator& operator--();

                    T& operator*() const;
                    iterator() ;


                private:
                    iterator(list<T>::nodo* a , bool pte=false) ;
                    list<T>::nodo* punt;
                    bool pastTheEnd;


    };
    list();
    list(const list&);
    ~list();
    void push_back(T);
    void insert(T);
    //Delete
    void pop_back();
    void remove(T);

    //Operator
    list<T>& operator=(const list&);

    //Getter
    bool is_empty() const;
    unsigned int size() const;


    //iterator
    iterator begin() const;
    iterator end() const;
    T& operator[](iterator) const;



};

//Nodo
template <class T>
list<T>::nodo::~nodo(){
    if(info!=nullptr){
        if(*info!=nullptr){
            delete *info;
        }

    }
};


//Nodo
template <class T>
list<T>::nodo::nodo(): next(0) , prev(0){};

template <class T>
list<T>::nodo::nodo(T& i, nodo* n ,nodo* p): info(new T(i)) , next(n) , prev(p) {};


//List

//Costruttore di default
template <class T>
list<T>::list() : first(0) , last(0) , sizel(0) {};

//Costruttore di Copia
template <class T>
list<T>::list(const list<T>& l) : first(0) , last(0) , sizel(0)  {
   *this = l;
}

//Distruttore
template <class T>
list<T>::~list(){
    if(first) {distruggi(first);}
}

//Distruzione Profonda
template <class T>
void list<T>::distruggi(nodo* n){
    nodo *q;
    while (n)
    {
        q=n;
        n=n->next;
        if(q){delete q;}

    }
}
//operator
template <class T>
list<T>& list<T>::operator=(const list<T>& l){
    if(this != &l){
        distruggi(first);
        sizel=0;
        for(nodo* tmp = l.first; tmp != nullptr; tmp=tmp->next){
             T* dato= new T(*(tmp->info));
             this->push_back((*dato)->clone());
            }
        sizel = l.sizel;
    }

    return *this;
}
//Operazioni su lista
template <class T>
void list<T>::push_back(T info){
    nodo* q=new nodo(info);
    if(sizel==0){
        first=last=q;
    }else{
        last->next=q;
        q->prev=last;
        last = q;
        last->next=0;
    }
    sizel++;
}



template <class T>
void list<T>::pop_back(){
    if(sizel==1){
        delete last;
        first=last=0;
    }
    else if(!is_empty()){
        nodo *p = last;
        last=p->prev;

        delete p;
        last->next=0;
    }
    if(sizel>0)sizel--;
}



template <class T>
void list<T>::remove(T i){
    nodo* q=first;
    while(q!=0 && !(*(q->info)==i)){
        q=q->next;
    }
    if(q){
        if(q==first && q==last){          
           first=last=0;
        }
        else if(q->prev==0){ 
            (q->next)->prev=0;
            first = q->next;
        }else if(q->next==0){
            (q->prev)->next=0;
            last = q->prev;
        }else{
            (q->prev)->next = q->next;
            (q->next)->prev = (q->prev);
        }
        delete q;
        sizel--;
    }else{
        std::cout << "DATO NON PRESENTE" ;
    }

}

//Operazioni generiche
template <class T>
unsigned int list<T>::size() const{
    return sizel;
}

template <class T>
bool list<T>::is_empty() const{
    return sizel==0;
}



template <class T>
std::ostream &operator<<(std::ostream &os, const list<T>& b){
    typename list<T>::nodo* q = b.first;
    while(q){
        os << *(q->info) << " ";
        q=q->next;
    }
    os << std::endl;
    return os;
}

//ITERATOR
template <class T>
list<T>::iterator::iterator() : punt(0) , pastTheEnd(false) {};

template <class T>
list<T>::iterator::iterator(list<T>::nodo* a , bool pte) : punt(a) , pastTheEnd(pte) {};

template <class T>
T& list<T>::iterator::operator*() const {
    return *(punt->info);
}

template <class T>
bool list<T>::iterator::operator!=(iterator i) const {
    return punt!=i.punt;
}

template <class T>
bool list<T>::iterator::operator==(iterator i) const {
    return punt==i.punt;
}

template <class T>
typename list<T>::iterator list<T>::begin() const{
    if(first!=0) return iterator(first);
    return iterator();
}

template <class T>
typename list<T>::iterator list<T>::end() const{
    if(first==0) return iterator();
    return iterator(last+1,true);
}

template <class T>
T& list<T>::operator[](iterator i) const{
    return *(i.punt->info);
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator++(){
    if(punt && !pastTheEnd){
        if(punt->next==0) {punt = punt + 1; pastTheEnd = true;}
        else {punt = punt->next;}
    }
        return *this;

}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator--(){
    if(punt){

    if(pastTheEnd==true) {punt = punt - 1; pastTheEnd = false;}
    else if(punt->prev==0) punt = 0;
    else punt = punt ->prev;
    }
    return *this;
}



#endif // DLIST_H
