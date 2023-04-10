#ifndef ARTIFACTCARD_H
#define ARTIFACTCARD_H
#include "abstractcard.h"

class artifactCard : public Card{
private:
    std::string type;
    unsigned int damage;
    unsigned int defense;
protected:
    std::ostream& print(std::ostream& os) const override;
public:
    artifactCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string t, unsigned int dam = 0, unsigned int dif = 0 , bool status = 0);
    void setGrade() override;
    bool operator==(const Card& c) const override;
    Json::Value serialize() const override;
    virtual artifactCard* clone() const override;

};
#endif // ARTIFACTCARD_H
