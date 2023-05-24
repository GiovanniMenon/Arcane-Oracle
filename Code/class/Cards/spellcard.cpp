#include "spellcard.h"

spellCard::spellCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string el ,unsigned int danno, bool status) : EffectCards(n,d,b64U,c,eff,status), element(el) , dmg(danno){}

std::string spellCard::getElement() const {return element;}
int spellCard::getDamage() const {return dmg;}

std::ostream& spellCard::print(std::ostream& os) const{
    EffectCards::print(os);
    os << "Element: " << element << std::endl << "Scale: "  << std::endl;
    return os;
}

bool spellCard::operator==(const Card& c) const {
    const spellCard* r = dynamic_cast<const spellCard*> (&c);
    return r && EffectCards::operator==(c) && element == r->getElement();
}


Json::Value spellCard::serialize() const{
    Json::Value json;
    Json::Reader reader;
    json = EffectCards::serialize();

    json["type"] = 2;
    json["element"] = getElement();
    json["attack_points"] = dmg;

    return json;
}

spellCard* spellCard::clone() const { return new spellCard (*this);}

//Visitor
void spellCard::accept(Visitor*v) {
    v->visit(this);
}

void spellCard::setDamage(unsigned int newDamage){
    dmg = newDamage;
}

void spellCard::setElement(const std::string& newElement){
    element = newElement;
}
