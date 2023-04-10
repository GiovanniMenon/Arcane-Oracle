#include "spellcard.h"

spellCard::spellCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string el , bool status) : EffectCards(n,d,b64U,c,eff,status), element(el){}

std::string spellCard::getElement() const {return element;}


std::ostream& spellCard::print(std::ostream& os) const{
    EffectCards::print(os);
    os << "Element: " << element << std::endl << "Scale: "  << std::endl;
    return os;
}

bool spellCard::operator==(const Card& c) const {
    const spellCard* r = dynamic_cast<const spellCard*> (&c);
    return r && EffectCards::operator==(c) && element == r->getElement();
}

void spellCard::setGrade() {
    //Da fare
}

Json::Value spellCard::serialize() const{
    Json::Value json;
    Json::Reader reader;
    json = EffectCards::serialize();

    json["type"] = 2;
    json["element"] = getElement();
    json["grade"] = grade;

    return json;
}

spellCard* spellCard::clone() const { return new spellCard (*this);}
