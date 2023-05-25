#include "artifactcard.h"

artifactCard::artifactCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string t, unsigned int dam, unsigned int dif , bool status) : Card(n,d,b64U, c,status), type(t), damage(dam), defense(dif){}


unsigned int damageCompare = 50;
unsigned int defCompare = 30;
unsigned int healthCompare = 20;

std::string  artifactCard::getType() const{
    return type;
}
unsigned int artifactCard::getDamage() const{
    return damage;
}
unsigned int artifactCard::getDefense() const{
    return defense;
}



bool artifactCard::operator==(const Card& c) const{
    return Card::operator==(c);
}

Json::Value  artifactCard::serialize() const {
   Json::Value json;
   Json::Reader reader;
   json = Card::serialize();

   json["type"] = 5;
   json["artifact_type"] = type;
   json["attack_points"] = damage;
   json["defense_points"] = defense;


   return json;
}

artifactCard* artifactCard::clone() const { return new artifactCard(*this); }


//Metodi Visitor

void artifactCard::accept(Visitor* v) {
    v->visit(this);
}
void artifactCard::setType(const std::string& newtype) {
    type = newtype;
}

void artifactCard::setDamage(unsigned int newdam) {
    damage = newdam;
}

void artifactCard::setDefense(unsigned int newdef) {
    defense = newdef;
}
