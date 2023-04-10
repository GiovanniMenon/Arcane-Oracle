#ifndef EFFECTCARDS_H
#define EFFECTCARDS_H
#include "abstractcard.h"

class EffectCards : public Card{ //effectCards non implementa il metodo setGrade quindi anche lei è astratta pura
private:
    std::string effect;
protected:
    std::ostream& print(std::ostream& os) const override;
public:
    EffectCards(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff , bool status = 0);
    std::string getEffect() const;
    virtual  Json::Value  serialize() const override;
    bool operator ==(const Card&) const override;
    virtual ~EffectCards();
};

#endif // EFFECTCARDS_H
