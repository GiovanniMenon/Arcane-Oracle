#include "deck.h"
#include "../Cards/monstercard.h"
#include "../Cards/artifactcard.h"
#include "../Cards/territorycard.h"
#include "../Cards/spellcard.h"
#include "../Cards/trapcard.h"
#include <QDir>
#include <QFileInfo>
#include <QRadioButton>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QDirIterator>



//Metodi Per il controllo

bool Deck::verifyInput(const std::string &name){
    //PRE : data una stringa
    //Post : verifica che essa non contiene caratteri non accessibili
    char slash = '/';
    char backslash = '\\';
    char dollar = '$';

    for(unsigned int i=0; i < name.size() ; i++ ){
        if(name[i] == slash || name[i] == backslash || name[i] == dollar)
             return 1;
    }
    return 0;
}
bool Deck::verifyDeckName(const std::string &name){
    //PRE : data una stringa
    //Post : verifica che non esistono deck con quel nome
    QString path = "asset/Deck/";

    QDir directory(path);
    directory.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    std::string name_space = name;
    name_space.erase(std::remove_if(name_space.begin(), name_space.end(), ::isspace),
          name_space.end());

    QFileInfoList fileList = directory.entryInfoList();

    foreach(QFileInfo directory, fileList) {
        std::string Deck_name = directory.fileName().toStdString();

        if(name==Deck_name || name_space==Deck_name)   return 1;

    }

    return 0;
}
bool Deck::verifyCardName(const std::string &card_name) const {

    //PRE : data una stringa
    //POST: ritorna 0 se non esiste una carta con quel nome, ritorna 1 se esiste una carta con quel nome.
    bool find = 0;

    for(list<Card*>::iterator it = deck.begin(); it!=deck.end() ; ++it){

            if(card_name==deck[it]->getName()){
                find = 1;

                break;
            }
    }
    if(!find){
        std::ifstream ifs(deck_folder_path + "/database.json");

        if(ifs){

        Json::Reader reader;
        Json::Value obj;
        reader.parse(ifs,obj);
        const Json::Value& cards=obj["Cards"];

        if(cards.size()!=0){

        for(unsigned int i=0;i < cards.size();i++){
            if(card_name==cards[i]["name"].asString()){
                find = 1;
                break;
            }
            }
        }
        }
        ifs.close();
    }
    return find;

}

//Costruttori e Setter
Deck::Deck() : deck() {
        mkdir("asset/", 0777);
        mkdir("asset/Deck/", 0777);
}
void Deck::SetDeck(std::string Deck_name )  {

            name = Deck_name;

            Deck_name.erase(std::remove_if(Deck_name.begin(), Deck_name.end(), ::isspace),
                  Deck_name.end());


            deck_folder_path = "asset/Deck/" + Deck_name;

            int folder = mkdir(deck_folder_path.c_str() , 0777);
            if(folder == 0 ){
                std::ofstream file(deck_folder_path + "/database.json", std::ios::out);
                mkdir(std::string(deck_folder_path + std::string("/CardImg")).c_str() , 0777);
                mkdir(std::string(deck_folder_path + std::string("/Card")).c_str() , 0777);
                //salvo il nome del deck
                save();
            }else{
                //Se esiste gia' un deck con quel nome
                load();
            }

}

//Getter
std::string Deck::getName() const { return name;}
unsigned int Deck::size() const { return deck.size();}
bool Deck::is_empty() const { return deck.is_empty();}
Card* Deck::prec(Card* c) const {
    list<Card*>::iterator it = deck.begin();
    while(!(*(deck[it])==(*c)))
    {
        ++it;
    }

    if(it==deck.begin()){
        it = deck.end();
        --it;
        return deck[it];
    }
    else{
         --it;
         return deck[it];
    }


}
Card* Deck::last() const {
    list<Card*>::iterator it = deck.end();
    --it;

    return deck[it];
}
Card* Deck::next(Card* c) const {
    list<Card*>::iterator it = deck.begin();
    while(!(*(deck[it])==(*c)))
    {
        ++it;
    }
    ++it;
    if(it==deck.end()) return deck[deck.begin()];
    else return deck[it];
}

// Metodi Deck
void Deck::insert(Card* c){
       if(c!=nullptr) deck.push_back(c);
}
void Deck::remove(){
        deck.pop_back();
}
void Deck::removeElement(Card *c){
           deck.remove(c);
}
Card* Deck::operator[](unsigned int pos) const{
        if(pos > deck.size()) return nullptr;
        list<Card*>::iterator it = deck.begin();
        for(unsigned int i=0; i!=pos; ++it){
                    i++;
        }
        return deck[it];
}
void Deck::clear()  {
    //PRE : Dato un mazzo che contiente della carte o anche vuoto
    //POST: Cancella tutto il mazzo ed elimina le carte non salvate e le relative immagini
    int n = deck.size();
    for(int i=0;i<n; i++){
        remove();
    }
}
Deck* Deck::search(std::string string)  const {
    //Pre: Data una stringa
    //POST : Ritorna un mazzo costituito da tutte le carte che hanno quella stringa nel nome o nella descrizione
    transform(string.begin(), string.end(), string.begin(), ::tolower);

    Deck* tmp = new Deck();
    tmp -> deck = deck.search(string);
    return tmp;

}

Deck* Deck::filter(const int i)  const {
    //Pre: Data una stringa
    //POST : Ritorna un mazzo costituito da tutte le carte che hanno quella stringa nel nome o nella descrizione
    Deck* tmp = new Deck();
    for(list<Card*>::iterator it = deck.begin(); it !=  deck.end(); ++it )
           {
        switch (i) {
        case 1:
            if(dynamic_cast<monsterCard*>(deck[it])!=nullptr)
            {
               //Copia profonda della carta
               tmp->insert(deck[it]->clone());
            }
            break;
        case 2:
            if(dynamic_cast<territoryCard*>(deck[it])!=nullptr)
            {
               //Copia profonda della carta
               tmp->insert(deck[it]->clone());
            }

            break;
        case 3:
            if(dynamic_cast<artifactCard*>(deck[it])!=nullptr)
            {
               //Copia profonda della carta
               tmp->insert(deck[it]->clone());
            }
            break;
        case 4:
            if(dynamic_cast<spellCard*>(deck[it])!=nullptr)
            {
               //Copia profonda della carta
               tmp->insert(deck[it]->clone());
            }
            break;
        case 5:
            if(dynamic_cast<trapCard*>(deck[it])!=nullptr)
            {
               //Copia profonda della carta
               tmp->insert(deck[it]->clone());
            }
            break;
        default:
            break;
        }



           }
    return tmp;

}
void Deck::order(int option, bool ord){
    //PRE: Dato un mazzo
    //POST: Ordina il mazzo con diversi criteri
        if(ord){
            switch(option){
            case 1:
                //Nome
                for(list<Card*>::iterator it = deck.begin(); it!=deck.end();++it){

                    std::string string1 = deck[it]->getName();
                    transform(string1.begin(), string1.end(), string1.begin(), ::tolower);

                    for(list<Card*>::iterator i = it ; i!=deck.end();++i){


                        std::string string2 = deck[i]->getName();
                        transform(string2.begin(), string2.end(), string2.begin(), ::tolower);

                        if(string1[0]>string2[0]){


                            Card* tmp = deck[it];
                            deck[it]=deck[i];
                            deck[i]=tmp;

                            string1 = deck[it]->getName();
                            transform(string1.begin(), string1.end(), string1.begin(), ::tolower);

                        }
                    }
                }
                break;
            case 2:
                //Costo
                for(list<Card*>::iterator it = deck.begin(); it!=deck.end();++it){

                    for(list<Card*>::iterator i = it ; i!=deck.end();++i){

                        if(deck[it]->getCost()>deck[i]->getCost()){

                            Card* tmp = deck[it];
                            deck[it]=deck[i];
                            deck[i]=tmp;

                        }
                    }
                }
                break;

        }
        }else{
                switch(option){
                case 1:
                    //Name
                    for(list<Card*>::iterator it = deck.begin(); it!=deck.end();++it){
                        std::string string1 = deck[it]->getName();
                        transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
                        for(list<Card*>::iterator i = it ; i!=deck.end();++i){
                            std::string string2 = deck[i]->getName();
                            transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
                            if(string1[0]<string2[0]){
                                Card* tmp = deck[it];
                                deck[it]=deck[i];
                                deck[i]=tmp;
                                string1 = deck[it]->getName();
                                transform(string1.begin(), string1.end(), string1.begin(), ::tolower);

                            }
                        }
                    }
                    break;
                case 2:
                    //Costo
                    for(list<Card*>::iterator it = deck.begin(); it!=deck.end();++it){
                        for(list<Card*>::iterator i = it ; i!=deck.end();++i){
                            if(deck[it]->getCost()<deck[i]->getCost()){
                                Card* tmp = deck[it];
                                deck[it]=deck[i];
                                deck[i]=tmp;
                            }
                        }
                    }
                    break;

            }
    }

};

// Metodi Per la gestione dei dati
void Deck::load() {
    //PRE : Si ha un mazzo
    //POST : Si legge da file e si caricano le carte lette nel mazzo.
    clear();
    std::ifstream ifs(deck_folder_path + "/database.json");
    if(ifs){
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs,obj);
    const Json::Value& cards=obj["Cards"];
    const Json::Value& Saved_Name=obj["Name"];
    name = Saved_Name.asString();
    if(cards.size()!=0){
    Card* tmp;
    for(unsigned int i=0;i < cards.size();i++){
        switch(cards[i]["type"].asInt()){
                    case 1:tmp = new monsterCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["level"].asInt(),cards[i]["health"].asInt(),cards[i]["attack_points"].asInt(),cards[i]["defense_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 2:tmp = new spellCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(),cards[i]["element"].asString(),cards[i]["attack_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 3:tmp = new territoryCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(), cards[i]["type_effect"].asString(),cards[i]["save"].asBool());
                           break;
                    case 4:tmp = new trapCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(),cards[i]["damage"].asInt(),cards[i]["duration"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 5:tmp = new artifactCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["artifact_type"].asString(),cards[i]["attack_points"].asInt(),cards[i]["defense_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    default:tmp=nullptr;
                }

        deck.push_back(tmp);
    }
    ifs.close();
    }}
}
void Deck::save() {
    //PRE : Si ha un mazzo
    //POST : Si scrive nel file le carte del proprio mazzo. Si invoca il garbage Collector per evitare garbage
    if(deck.size()!=0){
    garbage_collector();

    std::ofstream ofs(deck_folder_path + "/database.json");
    if(ofs){
    Json::Value obj;
    Json::Value cards(Json::arrayValue);
    Json::Value card;

    for(list<Card*>::iterator it = deck.begin(); it !=  deck.end(); ++it){
        deck[it]->set_status();
        cards.append(deck[it]->serialize());
    }
    obj["Cards"]=cards;
    obj["Name"] = getName();

    ofs << obj;
    ofs.close();
    }
    }else{
        std::ofstream ofs(deck_folder_path + "/database.json");
        Json::Value obj;

        obj["Name"] = getName();
        ofs << obj;
        ofs.close();
    }

}
void Deck::garbage_collector() {
    //PRE : Si ha un mazzo salvato
    //POST :Si eliminano le immagini delle carte che non compaiono piu' nel nuovo salvataggio rispetto al precedente.
    //      in questo modo si evitano immagini di carte salvate e poi eliminate.
    std::ifstream ifs(deck_folder_path + "/database.json");
    Deck deck_tmp;
    if(ifs){
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs,obj);
    const Json::Value& cards=obj["Cards"];
    if(cards.size()!=0){
    Card* tmp;
    for(unsigned int i=0;i < cards.size();i++){
        switch(cards[i]["type"].asInt()){
                    case 1:tmp = new monsterCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["level"].asInt(),cards[i]["health"].asInt(),cards[i]["attack_points"].asInt(),cards[i]["defense_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 2:tmp = new spellCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(),cards[i]["element"].asString(),cards[i]["attack_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 3:tmp = new territoryCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(), cards[i]["type_effect"].asString(),cards[i]["save"].asBool());
                           break;
                    case 4:tmp = new trapCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["effect"].asString(),cards[i]["damage"].asInt(),cards[i]["duration"].asInt(),cards[i]["save"].asBool());
                           break;
                    case 5:tmp = new artifactCard(cards[i]["name"].asString(),cards[i]["description"].asString(),cards[i]["b64url"].asString(),cards[i]["cost"].asInt(),cards[i]["artifact_type"].asString(),cards[i]["attack_points"].asInt(),cards[i]["defense_points"].asInt(),cards[i]["save"].asBool());
                           break;
                    default:tmp=nullptr;
                }
        deck_tmp.insert(tmp);
        }
    bool find;
    for(list<Card*>::iterator it_tmp = deck_tmp.deck.begin() ; it_tmp!=deck_tmp.deck.end() ; ++it_tmp){
            find = 0;
            for(list<Card*>::iterator it_deck = deck.begin() ; it_deck!=deck.end() ; ++it_deck){
                if(*(deck[it_deck])==*(deck_tmp.deck[it_tmp])){
                    find = 1;
                    break;
                }
            }
            if(find==0){
                ::remove(deck_tmp.deck[it_tmp]->getUrl().c_str());

                std::string imgPath = deck_tmp.deck[it_tmp]->getUrl();

                std::string searchString = "Card";
                size_t lastSlashPos = imgPath.find_last_of('/');
                size_t secondLastSlashPos = imgPath.find_last_of('/', lastSlashPos - 1);
                size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
                size_t index = imgPath.find(searchString, secondLastSlashPos + 1);
                if (index != std::string::npos) {
                        imgPath.replace(index, substringLength, "CardImg");
                    }
                ::remove(imgPath.c_str());
            }

        }
    }
    }
    ifs.close();
}
