#ifndef SPELLWIDGET_H
#define SPELLWIDGET_H

#include <QWidget>


#include "effectwidget.h"
#include "../../class/Cards/spellcard.h"


class spellWidget : public effectWidget
{
    Q_OBJECT
public:
    spellWidget(Deck * , QWidget *parent=nullptr);

    virtual Card* getInput() override;

    virtual bool checkInput() const override ;
    virtual void generate() override ;
public slots:
    void onImageClickedSlot();
private:
    std::vector <std::string> spellElement;
    int idSpell;

    QLabel * spellType;
    QLabel * title;
    QLineEdit *spellDmg;

    ClickableLabel* flame;
    ClickableLabel* air;
    ClickableLabel* ground;
    ClickableLabel* ocean;

    ClickableLabel* thunder;
    ClickableLabel* storm;
    ClickableLabel* ice;
    ClickableLabel* time;
    ClickableLabel* poison;







};
#endif // SPELLWIDGET_H
