#include "artifactcard.h"

artifactCard::artifactCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string t, unsigned int dam, unsigned int dif , bool status) : Card(n,d,b64U, c,status), type(t), damage(dam), defense(dif){}


unsigned int damageCompare = 50;
unsigned int defCompare = 30;
unsigned int healthCompare = 20;


std::ostream& artifactCard::print(std::ostream& os) const{
    Card::print(os);
    os << "Tipo: " << type <<std::endl<< "Attacco: " << damage <<std::endl<< "Difesa: " << defense <<std::endl<< "Salute: "  <<std::endl<< "Scale: " <<std::endl<< "Ncard Generated:" << std::endl<<std::endl;
    return os;
}

bool artifactCard::operator==(const Card& c) const{
    const artifactCard* r = dynamic_cast<const artifactCard*> (&c);
    return r && Card::operator==(c) && r->damage == damage && r->defense == defense && r->type == type;
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
