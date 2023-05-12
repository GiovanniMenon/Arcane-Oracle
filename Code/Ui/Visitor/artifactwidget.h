#ifndef ARTIFACTWIDGET_H
#define ARTIFACTWIDGET_H


#include <QWidget>
#include "cardwidget.h"
#include "../../class/Cards/artifactcard.h"

class artifactWidget : public cardWidget
{
    Q_OBJECT
public:
    artifactWidget(Deck * , QWidget *parent=nullptr);
    virtual Card* getInput() override;

    virtual bool checkInput() const override ;
    virtual void generate() override ;
public slots:
    void onImageClickedSlot();
private:
    std::vector<std::string> artifactType;
    QLineEdit * cardAtt;
    QLineEdit * cardDef;
    QLabel* artType;
    QLabel* artTypeText;
    QLabel* title;
    int id;

    ClickableLabel* armor;
    ClickableLabel* potions;
    ClickableLabel* magic;


};
#endif // ARTIFACTWIDGET_H
