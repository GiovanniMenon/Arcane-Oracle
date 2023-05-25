#include "effectcards.h"

EffectCards::EffectCards(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff , bool status) : Card(n,d,b64U, c , status), effect(eff){}

std::string EffectCards::getEffect() const {return effect;}


bool EffectCards::operator==(const Card& c) const{

    return Card::operator==(c);
}

Json::Value  EffectCards::serialize() const {
    Json::Value json;

    json = Card::serialize();
    json["effect"] = getEffect();

    return json;
}

EffectCards::~EffectCards() {}

//Metodi Visitor
void EffectCards::setEffectBase(const std::string& newEffect){
    effect = newEffect;
}

