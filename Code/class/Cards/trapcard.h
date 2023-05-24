#ifndef TRAPCARD_H
#define TRAPCARD_H
#include "effectcards.h"
#include "../../Ui/Visitor/visitor.h"

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

    void setDamage(const unsigned int&newDamage);
    void setDuration(const unsigned int& newDuration);
    void setEffect(const std::string& newEffect);

    bool operator ==(const Card&) const override;
    Json::Value serialize() const override;
    virtual trapCard* clone() const override;

    //visitor
    void accept(Visitor*) override;


};

#endif // TRAPCARD_H
