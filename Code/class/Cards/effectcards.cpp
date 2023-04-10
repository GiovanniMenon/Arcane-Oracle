#include "effectcards.h"

EffectCards::EffectCards(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff , bool status) : Card(n,d,b64U, c , status), effect(eff){}

std::string EffectCards::getEffect() const {return effect;}

std::ostream& EffectCards::print(std::ostream& os) const{
    Card::print(os);
    os << "Effect: " << effect << std::endl;
    return os;
}

bool EffectCards::operator==(const Card& c) const{
    const EffectCards * r = dynamic_cast<const EffectCards*> (&c);
    return r && Card::operator==(c) && r->getEffect() == effect;
}

Json::Value  EffectCards::serialize() const {
    Json::Value json;

    json = Card::serialize();
    json["effect"] = getEffect();

    return json;
}

EffectCards::~EffectCards() {}

