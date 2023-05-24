#ifndef EFFECTWIDGET_H
#define EFFECTWIDGET_H



#include <QWidget>

#include <QWidget>
#include "cardwidget.h"
#include "../../class/Cards/effectcards.h"


class effectWidget : public cardWidget
{
    Q_OBJECT
public:
    effectWidget(Deck * , QWidget *parent=nullptr);

    virtual bool checkInput() const override ;
    virtual void generate() override ;
public slots:
    void setFieldsCardSlot() override;
protected:
    QTextEdit *effect;

};


#endif // EFFECTWIDGET_H
