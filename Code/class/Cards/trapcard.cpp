#include "trapcard.h"

trapCard::trapCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, unsigned int dam, unsigned int du , bool status) : EffectCards(n,d,b64U, c, eff , status), damage(dam), duration(du){}

unsigned int trapCard::getDamage() const { return damage;}
unsigned int trapCard::getDuration() const { return duration;}


unsigned int durationCompare = 5; //seconds
unsigned int trapDamageCompare = 10;

void trapCard::setGrade() {
    if(duration > durationCompare){
        if(damage > trapDamageCompare){
            grade = 3; //ultra rare trap card
            return;
        }
        grade = 2; //rare
        return;
    }
    grade = 1; //common
}

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
    json["grade"] = grade;
    json["type"] = 4;

    return json;
}

trapCard* trapCard::clone() const { return new trapCard(*this);}
