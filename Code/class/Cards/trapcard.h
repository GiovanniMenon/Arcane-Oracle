#ifndef TRAPCARD_H
#define TRAPCARD_H
#include "effectcards.h"

class trapCard : public EffectCards {
private:
    unsigned int damage;
    unsigned int duration; //checks how much time the trapCard is activeted
protected:
    std::ostream& print(std::ostream& os) const override;
public:
    trapCard(std::string n, std::string d, std::string b64U, unsigned int c, std::string eff, unsigned int dam = 0, unsigned int du = 1,bool status = 0);
    unsigned int getDamage() const;
    unsigned int getDuration() const;
    void setGrade() override;
    bool operator ==(const Card&) const override;
    Json::Value serialize() const override;
    virtual trapCard* clone() const override;
};

#endif // TRAPCARD_H
