#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>


#include "effectwidget.h"
#include "../../class/Cards/territorycard.h"


class fieldWidget : public effectWidget
{
    Q_OBJECT
public:
    fieldWidget(Deck * , QWidget *parent=nullptr);

    virtual Card* getInput() override;

    virtual bool checkInput() const override ;
    virtual void generate() override ;
public slots:
    void onImageClickedSlot();
private:
    std::vector <std::string> elements;
    int id;
    QLabel * fieldType;
    QLabel * LabelElement;
    QHBoxLayout *elementMenu;

    ClickableLabel* earth;
    ClickableLabel* wind;
    ClickableLabel* fire;
    ClickableLabel* water;



};

#endif // FIELDWIDGET_H
