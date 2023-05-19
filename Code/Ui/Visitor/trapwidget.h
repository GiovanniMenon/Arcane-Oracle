#ifndef TRAPWIDGET_H
#define TRAPWIDGET_H

#include <QWidget>
#include "effectwidget.h"
#include "../../class/Cards/trapcard.h"

class trapWidget : public effectWidget
{
    Q_OBJECT
public:
    trapWidget(Deck * , QWidget *parent=nullptr);

    virtual Card* getInput() override;
    virtual void generate() override ;
    virtual bool checkInput() const override ;
private:
    QLineEdit *spellDmg;
    QLineEdit *durata;
};

#endif // TRAPWIDGET_H
