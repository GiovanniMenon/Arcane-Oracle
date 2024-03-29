#ifndef MONSTERCARD_H
#define MONSTERCARD_H
#include "abstractcard.h"
#include "../../Ui/Visitor/visitor.h"

class monsterCard : public Card{
private:
    unsigned int level;
    unsigned int health;
    unsigned int damage;
    unsigned int defense;
public:
    monsterCard(std::string n, std::string d, std::string b64u,unsigned int c, unsigned int l = 1, unsigned int lp = 100, unsigned int ap = 0, unsigned int dp = 0 , bool status = 0);
    unsigned int getLevel() const;
    unsigned int getHealth() const;
    unsigned int getDamage() const;
    unsigned int getDefense() const;

    void setLevel(unsigned int newLevel);
    void setHealth(unsigned int newHealth);
    void setDamage(unsigned int newDamage);
    void setDefense(unsigned int newDefense);

    bool operator ==(const Card&) const override;
    virtual monsterCard* clone() const override;
    Json::Value  serialize() const override;

    //Visitor
    void accept(Visitor*) override;


};


#endif // MONSTERCARD_H
