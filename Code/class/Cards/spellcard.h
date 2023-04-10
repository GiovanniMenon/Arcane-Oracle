#ifndef SPELLCARD_H
#define SPELLCARD_H
#include "effectcards.h"

class spellCard : public EffectCards{
private:
    std::string element;

protected:
    std::ostream& print(std::ostream& os) const override;
public:
    spellCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string el,bool status = 0);
    std::string getElement() const;
    bool getScale() const;
    bool operator ==(const Card&) const override;
    virtual  Json::Value  serialize() const override;
    void setGrade() override;
    virtual spellCard* clone() const override;
};

#endif // SPELLCARD_H
