#ifndef DECK_H
#define DECK_H


#ifdef __has_include
#if __has_include(<jsoncpp/json/json.h>)
#include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif
#else
#include <json/json.h>
#endif

#include "../Cards/abstractcard.h"
#include "../Template/Dlist.h"
#include <cstdio>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <dirent.h>


#include <list>

class Deck
{
friend std::ostream &operator<<(std::ostream &os, const Deck& deck);
public: Deck();
        void SetDeck(std::string);
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
        Card* last() const;

        void search(std::string) const;
        void order(int , bool);


        void save() ;
        void garbage_collector() ;
        void load() ;

        Card* operator[](unsigned int) const;


        bool verifyCardName(const std::string &) const ;
        static bool verifyDeckName(const std::string &) ;
        static bool verifyInput(const std::string &);
    private:
        list<Card*> deck;
        std::string name;
        std::string deck_folder_path;


};

#endif // DECK_H
