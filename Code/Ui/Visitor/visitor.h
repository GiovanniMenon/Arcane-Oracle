#ifndef VISITOR_H
#define VISITOR_H

#include <QWidget>
#include "cardwidget.h"

class monsterCard;
class territoryCard;
class artifactCard;
class spellCard;
class trapCard;


class Visitor {
private:
    cardWidget* widget;
public:
    void visit(const monsterCard *obj);
    void visit(const territoryCard*);
    void visit(const artifactCard*);
    void visit(const spellCard*);
    void visit(const trapCard*);
    cardWidget* getWidget() const;
};


#endif // VISITOR_H
