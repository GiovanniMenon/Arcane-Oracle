#ifndef ARTIFACTCARD_H
#define ARTIFACTCARD_H
#include "abstractcard.h"
#include "../../Ui/Visitor/visitor.h"

class artifactCard : public Card{
private:
    std::string type;
    unsigned int damage;
    unsigned int defense;
public:
    artifactCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string t, unsigned int dam = 0, unsigned int dif = 0 , bool status = 0);

    std::string  getType() const;
    unsigned int getDamage() const;
    unsigned int getDefense() const;

    void setType(const std::string& newType);
    void setDamage(unsigned int newdam);
    void setDefense(unsigned int newdef);

    bool operator==(const Card& c) const override;
    Json::Value serialize() const override;
    virtual artifactCard* clone() const override;

    //Visitor
    void accept(Visitor*) override;



};
#endif // ARTIFACTCARD_H
