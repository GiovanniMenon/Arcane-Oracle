#include "monstercard.h"

monsterCard::monsterCard(std::string n, std::string d, std::string b64u,unsigned int c, unsigned int l, unsigned int lp, unsigned int ap, unsigned int dp , bool status) : Card(n,d,b64u,c , status), level(l), health(lp), damage(ap), defense(dp){}

unsigned int monsterCard::getLevel() const {return level;}
unsigned int monsterCard::getHealth() const {return health;}
unsigned int monsterCard::getDamage() const {return damage;}
unsigned int monsterCard::getDefense() const {return defense;}


unsigned int attackCompare = 70;            //variables to compare the stats given to the card to set the Grade
unsigned int defenseCompare = 40;
unsigned int Lifecompare = 100;
unsigned int LevelCompare = 10;




std::ostream& monsterCard::print(std::ostream& os) const {
    Card::print(os);
    os <<"Attack Point: " << damage <<std::endl<< "Defense Point: " << defense <<std::endl<< "Life Points: " << health <<std::endl<< "Level: " << level <<std::endl<< "Card Generated: "  << std::endl;
    return os;
}

bool monsterCard::operator==(const Card& c) const {
    const monsterCard* r = dynamic_cast<const monsterCard*> (&c);
    return r && Card::operator==(c) && r->damage == damage && r->defense == defense && r->health == health && r->level == level;
}


Json::Value monsterCard::serialize() const {
   Json::Value json;
   Json::Reader reader;
   json = Card::serialize();


   json ["type"] = 1;
   json["level"] = level;
   json["health"] = health;
   json["attack_points"] = damage;
   json["defense_points"] = defense;




   return json;
}

monsterCard* monsterCard::clone() const { return new monsterCard(*this); }
