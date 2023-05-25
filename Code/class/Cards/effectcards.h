#ifndef EFFECTCARDS_H
#define EFFECTCARDS_H
#include "abstractcard.h"
#include "../../Ui/Visitor/visitor.h"

class EffectCards : public Card{ //effectCards non implementa il metodo setGrade quindi anche lei è astratta pura
private:
    std::string effect;
public:
    EffectCards(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff , bool status = 0);
    std::string getEffect() const;
    virtual  Json::Value  serialize() const override;
    bool operator ==(const Card&) const override;
    virtual ~EffectCards();

    //Visitor
    void setEffectBase(const std::string& newEffect);
};

#endif // EFFECTCARDS_H
