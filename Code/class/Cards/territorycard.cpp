#include "territorycard.h"

territoryCard::territoryCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string ty , bool status) : EffectCards(n,d,b64U, c, eff , status), type(ty){}

std::string territoryCard::getType() const {return type;}


bool territoryCard::operator==(const Card& c) const{
     return EffectCards::operator==(c);
}

//Tutte le carte territorio hanno lo stesso grado

Json::Value territoryCard::serialize() const {
    Json::Value json;
    Json::Reader reader;
    json = EffectCards::serialize();

    json["type"] = 3;
    json["type_effect"] = getType();


    return json;
}

territoryCard* territoryCard::clone() const{ return new territoryCard(*this);}

//visitor
void territoryCard::accept(Visitor* v) {
    v->visit(this);
}

void territoryCard::setType(const std::string& newType){
    type = newType;
}
