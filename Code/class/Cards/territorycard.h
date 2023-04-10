#ifndef TERRITORYCARD_H
#define TERRITORYCARD_H
#include "effectcards.h"

class territoryCard : public EffectCards{
private:
    std::string type;
protected:
    std::ostream& print(std::ostream& os) const override;
public:
    territoryCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string ty,bool status = 0);
    std::string getType() const;
    bool operator ==(const Card&) const override;
    virtual  Json::Value  serialize() const override;
    void setGrade() override;
    virtual territoryCard* clone() const override;
};

#endif // TERRITORYCARD_H

