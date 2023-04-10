#include "userInterface.h"
#include "Cards/monstercard.h"
#include "Cards/artifactcard.h"
#include "Cards/territorycard.h"
#include "Cards/spellcard.h"
#include "Cards/trapcard.h"
#include "Generator/dall_eapi.h"

UI::UI() {}
int UI::showOptions() const {
    int choice;
    std::cout << "\n\nOptions:\n\n1)Add Card\n2)Remove Card\n3)Show Deck\n4)Sort Deck\n5)Seach Card\n6)Save\n7)load\n8)Exit\n++++++++++++++++++++++++\n";
    std::cout << std::endl << "Ur choice:";
    std::cin >> choice;
    return choice;
}
Card* UI::addcard(std::string deck_name)  {
    DALL_E_generator e;
    std::string name,description, type, url="temp", effect;
    int cost,defend,attack,health,level,choice;

    Card* carta;
    std::cout << "\n+++++++\nType:\n\n1)Monster\n2)Artifact\n3)Territory\n4)Spell\n5)Trap\n\n";
    std::cout << std::endl << "Ur choice:";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(choice){
        case 1:
            std::cout << std::endl << "Name: ";
            std::getline(std::cin,name);
            std::cout << "Description: ";
            std::getline(std::cin,description);
            std::cout << "Cost: ";
            std::cin >> cost;
            std::cout << "Attack: ";
            std::cin >> attack;
            std::cout << "Defend: ";
            std::cin >> defend;
            std::cout << "Level: ";
            std::cin >> level;
            std::cout << "Health: ";
            std::cin >> health;
            std::cout <<  std::endl << "Generazione carta....." << std::endl;
            url = e.convert(e.generate(description),name,deck_name);
            carta = new monsterCard(name,description,url,cost,level,health,attack,defend);
        break;
        case 2:
            std::cout << std::endl << "Name: ";
            std::getline(std::cin,name);
            std::cout << "Description: ";
            std::getline(std::cin,description);
            std::cout << "Cost: ";
            std::cin >> cost;
            std::cout << "Attack: ";
            std::cin >> attack;
            std::cout << "Defend: ";
            std::cin >> defend;
            std::cout << "Level: ";
            std::cin >> level;
            std::cout << "Type: ";
            std::cin >> type;
            std::cout <<  std::endl << "Generazione carta....." << std::endl;
            url = e.convert(e.generate(description),name,deck_name);
            carta = new artifactCard(name,description,url,cost,type,attack,defend);
        break;
        case 3:
            std::cout << std::endl << "Name: ";
            std::getline(std::cin,name);
            std::cout << "Description: ";
            std::getline(std::cin,description);
            std::cout << "Effect: ";
            std::getline(std::cin,effect);
            std::cout << "Cost: ";
            std::cin >> cost;
            std::cout << "Type: ";
            std::cin >> type;
            std::cout <<  std::endl << "Generazione carta....." << std::endl;
            url = e.convert(e.generate(description),name,deck_name);
            carta = new territoryCard(name,description,url,cost,effect,type);
        break;
        case 4:
            std::cout << std::endl << "Name: ";
            std::getline(std::cin,name);
            std::cout << "Description: ";
            std::getline(std::cin,description);
            std::cout << "Effect: ";
            std::getline(std::cin,effect);
            std::cout << "Cost: ";
            std::cin >> cost;
            std::cout << "Element Type: ";
            std::cin >> type;
            std::cout <<  std::endl << "Generazione carta....." << std::endl;
            url = e.convert(e.generate(description),name,deck_name);
            carta = new spellCard(name,description,url,cost,effect,type);
        break;
        case 5:
            std::cout << std::endl << "Name: ";
            std::getline(std::cin,name);
            std::cout << "Description: ";
            std::getline(std::cin,description);
            std::cout << "Effect: ";
            std::getline(std::cin,effect);
            std::cout << "Cost: ";
            std::cin >> cost;
            std::cout << "Durability: ";
            std::cin >> level;
            std::cout << "Damage: ";
            std::cin >> attack;
            std::cout <<  std::endl << "Generazione carta....." << std::endl;
            url = e.convert(e.generate(description),name,deck_name);
            carta = new trapCard(name,description,url,cost,effect,attack,level);
        break;


    }
    std::cout << " :: Carta inserita correttamente";
    return carta;
};
unsigned int UI::remcard(Deck &mazzo) const {
        unsigned int choice;
        std::cout << mazzo;
        std::cout << "\nInserire il numero della carta da eliminare: ";
        std::cin >> choice;
        while(choice-1 >= mazzo.size()){
            std::cout << "\nIl numero inserito non e' presente, riprova: ";
            std::cin >> choice;
        }
        return choice-1;
    };


void UI::start(Deck &mazzo) {
    is_running = true;
    std::cout << "        UI Beta 0.2\n++++++++++++++++++++++++++++" ;
    while(is_running){
        int choice,x ;
        char sure;
        std::string string1;
        choice = showOptions();
        switch (choice){
        case 1:
                mazzo.insert(addcard(mazzo.getName()));
            break;
        case 2:
                mazzo.removeElement(mazzo[remcard(mazzo)]);
            break;
        case 3:
                std::cout << "MAZZO :       " << "size | " << mazzo.size() << "\n";
                std::cout << mazzo;
            break;
        case 4:
                std::cout << "Ordina per\n\n1)Nome\n2)Costo\nLa tua scelta : " ;
                std::cin >> x;
                mazzo.order(x,true);
                std::cout << mazzo;
            break;
        case 5:
                std::cout << "Cerca : " ;
                std::cin >> string1;
                mazzo.search(string1);
            break;
        case 6:
                std::cout << "Sei sicuro di voler salvare il mazzo corrente? In questo modo sovrascriverai i precedenti salvataggi il mazzo salvato.(y/n): ";
                std::cin >> sure;
                if(sure=='y') mazzo.save();
            break;
        case 7:

                std::cout << "Sei sicuro di voler caricare un mazzo salvato? In questo modo Cancellerai il mazzo corrente.(y/n): ";
                std::cin >> sure;
                if(sure=='y') mazzo.load();
            break;
        case 8:
                std::cout << "\nGood Bye..." ;
                is_running = false;
            break;
        default:
            std::cout << "Puoi inserire solo Interi" ;
            is_running = false;
            break;
        }



    }
}
