#include "trapwidget.h"

trapWidget::trapWidget(Deck * currDeck,QWidget *parent) : effectWidget(currDeck,parent)
{
    cardGroup ->setObjectName("cardTrap");
    spellDmg = new QLineEdit();
    durata = new QLineEdit();
    QIntValidator *validator = new QIntValidator();
    validator->setRange(1, 9);

    spellDmg->setValidator(validator);
    durata->setValidator(validator);
    QHBoxLayout *footer = new QHBoxLayout();


    footer -> addWidget(durata);

    footer -> addStretch();
    footer -> addWidget(spellDmg);

    inside -> addStretch();
    inside -> addLayout(footer);


    spellDmg -> setObjectName("AttAttr");
    durata -> setObjectName("TimeAttr");



    spellDmg ->setFixedSize(64,64);
    durata ->setFixedSize(64,64);


    durata -> setAlignment(Qt::AlignCenter);
    spellDmg -> setAlignment(Qt::AlignCenter);
}

Card* trapWidget::getInput() {
    return new trapCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(),effect->toPlainText().toStdString() ,spellDmg -> text().toInt(),durata->text().toInt());
}

bool trapWidget::checkInput() const{

    if(effectWidget::checkInput() && !(spellDmg ->text().simplified().isEmpty()) && !(durata ->text().simplified().isEmpty())){
        return 1;
    }else{
        return 0;
    }
}
