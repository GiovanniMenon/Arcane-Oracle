#include "monsterwidget.h"




monsterWidget::monsterWidget(Deck * currDeck,QWidget *parent) : cardWidget(currDeck,parent)
{
    cardGroup ->setObjectName("cardMonster");

    cardAtt = new QLineEdit();
    cardHP = new QLineEdit();
    cardDef = new QLineEdit();

    QHBoxLayout *footer = new QHBoxLayout();

    QIntValidator *validator = new QIntValidator();
    validator->setRange(1, 9);

    cardAtt->setValidator(validator);
    cardHP->setValidator(validator);
    cardDef->setValidator(validator);

    footer -> addWidget(cardHP);
    footer -> addWidget(cardDef);
    footer -> addStretch();
    footer -> addWidget(cardAtt);

    inside -> addStretch();
    inside -> addLayout(footer);


    cardAtt -> setObjectName("AttAttr");
    cardHP -> setObjectName("HPAttr");
    cardDef -> setObjectName("DefAttr");


    cardAtt ->setFixedSize(64,64);
    cardHP ->setFixedSize(72,72);
    cardDef ->setFixedSize(48,48);

    cardAtt -> setAlignment(Qt::AlignCenter);
    cardHP -> setAlignment(Qt::AlignCenter);
    cardDef -> setAlignment(Qt::AlignCenter);




}

Card* monsterWidget::getInput() {
    return new monsterCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(), 1,cardHP->text().toInt(),cardAtt->text().toInt(), cardDef->text().toInt());
}



bool monsterWidget::checkInput() const{

    if(cardWidget::checkInput() && !(cardAtt ->text().simplified().isEmpty()) && !(cardDef ->text().simplified().isEmpty()) && !(cardHP ->text().simplified().isEmpty())){
        return 1;
    }else{
        return 0;
    }
}
