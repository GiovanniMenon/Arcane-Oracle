#include "visitor.h"
#include "monsterwidget.h"
#include "artifactwidget.h"
#include "fieldwidget.h"
#include "spellwidget.h"
#include "trapwidget.h"

void Visitor::visit(const monsterCard *obj) {
    widget = new monsterWidget(const_cast<monsterCard*>(obj));
}

void Visitor::visit(const artifactCard *obj) {
    widget = new artifactWidget(const_cast<artifactCard*>(obj));
}

void Visitor::visit(const territoryCard *obj) {
    widget = new fieldWidget(const_cast<territoryCard*>(obj));
}

void Visitor::visit(const spellCard *obj) {
    widget = new spellWidget(const_cast<spellCard*>(obj));
}

void Visitor::visit(const trapCard *obj) {
    widget = new trapWidget(const_cast<trapCard*>(obj));
}


cardWidget* Visitor::getWidget() const {
    return widget;
}

