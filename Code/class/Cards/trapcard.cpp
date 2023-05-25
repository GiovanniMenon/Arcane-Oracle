#include "trapcard.h"

trapCard::trapCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, unsigned int dam, unsigned int du , bool status) : EffectCards(n,d,b64U, c, eff , status), damage(dam), duration(du){}

unsigned int trapCard::getDamage() const { return damage;}
unsigned int trapCard::getDuration() const { return duration;}


bool trapCard::operator==(const Card& c) const {
     return EffectCards::operator==(c);
}

Json::Value trapCard::serialize() const {
    Json::Value json;
    Json::Reader reader;
    json = EffectCards::serialize();

    json["damage"] = damage;
    json["duration"] = duration;
    json["type"] = 4;

    return json;
}

trapCard* trapCard::clone() const { return new trapCard(*this);}

//Visitor
void trapCard::accept(Visitor*v) {
    v->visit(this);
}

void trapCard::setDamage(const unsigned int& newDamage){
    damage = newDamage;
}

void trapCard::setDuration(const unsigned int& newDuration){
    duration = newDuration;
}

void trapCard::setEffect(const std::string& newEffect){
    setEffectBase(newEffect);
}
