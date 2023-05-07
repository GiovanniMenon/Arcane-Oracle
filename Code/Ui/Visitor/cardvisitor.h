
#include <QWidget>



class monsterCard;

class Territory;

class Trap;

class Spell;

class Artifact;

class Card;

class CardVisitor {
protected:
    QWidget *widget;
public:
    //virtual void visit( monsterCard *monster) {
       //widget = new monsterwidget(monster);
    //};



    virtual QWidget *getWidget() = 0;
};
