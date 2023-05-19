#ifndef MONSTERWIDGET_H
#define MONSTERWIDGET_H

#include <QWidget>
#include "cardwidget.h"
#include "../../class/Cards/monstercard.h"

class monsterWidget : public cardWidget
{
    Q_OBJECT
public:
    monsterWidget(Deck * , QWidget *parent=nullptr);
    monsterWidget(monsterCard,QWidget *parent=nullptr) ;
    virtual Card* getInput() override;
    virtual void generate() override ;
    virtual bool checkInput() const override ;
private:
    QLineEdit * cardAtt;
    QLineEdit * cardDef;
    QLineEdit * cardHP;

};

#endif // MONSTERWIDGET_H
