#ifndef TERRITORYCARD_H
#define TERRITORYCARD_H
#include "effectcards.h"
#include "../../Ui/Visitor/visitor.h"

class territoryCard : public EffectCards{
private:
    std::string type;
public:
    territoryCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, std::string ty,bool status = 0);

    std::string getType() const;

    void setType(const std::string& newType);

    bool operator ==(const Card&) const override;
    virtual  Json::Value  serialize() const override;
    virtual territoryCard* clone() const override;


    void accept(Visitor*) override;

};

#endif // TERRITORYCARD_H

