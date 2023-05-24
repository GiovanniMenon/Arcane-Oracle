#include "trapcard.h"

trapCard::trapCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, unsigned int dam, unsigned int du , bool status) : EffectCards(n,d,b64U, c, eff , status), damage(dam), duration(du){}

unsigned int trapCard::getDamage() const { return damage;}
unsigned int trapCard::getDuration() const { return duration;}


unsigned int durationCompare = 5; //seconds
unsigned int trapDamageCompare = 10;



std::ostream& trapCard::print(std::ostream& os) const{
    EffectCards::print(os);
    os << "Damage: " << damage <<std::endl<< "Duration: " << duration<<std::endl;
    return os;
}

bool trapCard::operator==(const Card& c) const {
    const trapCard* r = dynamic_cast<const trapCard*> (&c);
    return r && EffectCards::operator==(c) && duration == r->getDuration() && damage == r->getDamage();
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
