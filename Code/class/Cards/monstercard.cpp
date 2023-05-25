#include "monstercard.h"

monsterCard::monsterCard(std::string n, std::string d, std::string b64u,unsigned int c, unsigned int l, unsigned int lp, unsigned int ap, unsigned int dp , bool status) : Card(n,d,b64u,c , status), level(l), health(lp), damage(ap), defense(dp){}

unsigned int monsterCard::getLevel() const {return level;}
unsigned int monsterCard::getHealth() const {return health;}
unsigned int monsterCard::getDamage() const {return damage;}
unsigned int monsterCard::getDefense() const {return defense;}

bool monsterCard::operator==(const Card& c) const {
    return Card::operator==(c);
}

Json::Value monsterCard::serialize() const {
   Json::Value json;
   Json::Reader reader;
   json = Card::serialize();


   json["type"] = 1;
   json["level"] = level;
   json["health"] = health;
   json["attack_points"] = damage;
   json["defense_points"] = defense;




   return json;
}

monsterCard* monsterCard::clone() const { return new monsterCard(*this); }

void monsterCard::setLevel(unsigned int newLevel) {
    level = newLevel;
}

// Setter per il campo "health"
void monsterCard::setHealth(unsigned int newHealth) {
    health = newHealth;
}

// Setter per il campo "damage"
void monsterCard::setDamage(unsigned int newDamage) {
    damage = newDamage;
}

// Setter per il campo "defense"
void monsterCard::setDefense(unsigned int newDefense) {
    defense = newDefense;
}

//Visitor
void monsterCard::accept(Visitor* v) {
    v->visit(this);
}
