#ifndef USERINTERFACE_H
#define USERINTERFACE_H



#include <QString>

#include "Deck/deck.h"

class UI
{
private:
    bool is_running = false;

public:
    UI();
    void start(Deck &mazzo) ;
    void show() const ;
    int showOptions() const ;
    Card* addcard(std::string deck_name) ;
    unsigned int remcard(Deck &mazzo) const ;
    void end() ;
};

#endif // USERINTERFACE_H
