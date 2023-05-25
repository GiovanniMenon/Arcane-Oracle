#ifndef SPELLCARD_H
#define SPELLCARD_H
#include "effectcards.h"
#include "../../Ui/Visitor/visitor.h"

class spellCard : public EffectCards{
private:
    std::string element;
    int dmg;
public:
    spellCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string el, unsigned int dmg,bool status = 0);
    std::string getElement() const;
    int getDamage() const;

    void setElement(const std::string& newElement);
    void setDamage(unsigned int newDamage);

    bool operator ==(const Card&) const override;
    virtual  Json::Value  serialize() const override;
    virtual spellCard* clone() const override;



    //visitor
    void accept(Visitor*) override;
};

#endif // SPELLCARD_H
