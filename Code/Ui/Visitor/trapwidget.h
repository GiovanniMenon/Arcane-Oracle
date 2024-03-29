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
    trapWidget(trapCard*, QWidget *parent=nullptr);
    void manual() override;
    virtual Card* getInput() override;
    virtual void generate() override ;
    virtual bool checkInput() const override ;
public slots:
    void setFieldsCardSlot() override;
private:
    QLineEdit *spellDmg;
    QLineEdit *durata;
};

#endif // TRAPWIDGET_H
