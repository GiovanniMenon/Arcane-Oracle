#ifndef DECK_H
#define DECK_H

#include "../Cards/abstractcard.h"
#include "../Template/Dlist.h"
#include <cstdio>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include <json/json.h>
#include <list>

class Deck
{
friend std::ostream &operator<<(std::ostream &os, const Deck& deck);
public: Deck();
        Deck(std::string);
        ~Deck() {}

        //ADD or Delete Card

        void insert(Card*);
        void remove();
        void removeElement(Card *);

        //Metodi Standard

        void show() const;
        void clear();
        unsigned int size() const;
        bool is_empty() const;
        std::string getName() const ;

        Card* next(Card*) const;
        Card* prec(Card*) const;

        void search(std::string) const;
        void order(int , bool);
        bool find(const std::string &) const;

        void save() ;
        void garbage_collector() ;
        void load() ;

        Card* operator[](unsigned int) const;


    private:
        list<Card*> deck;
        std::string name;
        std::string deck_folder_path;


};

#endif // DECK_H
