
#include <QWidget>

class Monster;

class Territory;

class Trap;

class Spell;

class Artifact;

class Card;

class CardVisitor {
protected:
    QWidget *widget;
public:
    virtual void visit(const Monster &monster, bool toEdit = false) = 0;

    virtual void visit(const Territory &territory, bool toEdit = false) = 0;

    virtual void visit(const Trap &trap, bool toEdit = false) = 0;

    virtual void visit(const Spell &spell, bool toEdit = false) = 0;

    virtual void visit(const Artifact &Artifact, bool toEdit = false) = 0;

    virtual QWidget *getWidget() = 0;
};
