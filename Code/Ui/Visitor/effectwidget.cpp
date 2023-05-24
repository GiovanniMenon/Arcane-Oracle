#include "effectwidget.h"

effectWidget::effectWidget(Deck * currDeck,QWidget *parent) : cardWidget(currDeck,parent)
{

    effect = new QTextEdit();
    QLabel *effectTitle = new QLabel("Effetto");

    QFont font = effectTitle->font();
    font.setItalic(true);
    effectTitle->setFont(font);
    effect->setFont(font);

    effectTitle -> setAlignment(Qt::AlignCenter);
    effectTitle -> setObjectName("cardEffTitle");
    effect -> setObjectName("cardEff");
    effect -> setAlignment(Qt::AlignCenter);


    inside ->addWidget(effectTitle);
    inside -> addWidget(effect);
    inside ->addStretch();

    effect->setFixedHeight(70);
}



void effectWidget::generate(){
    effect -> setReadOnly(true);
    cardWidget::generate();
} ;
bool effectWidget::checkInput() const{

    if(cardWidget::checkInput() && !(effect -> toPlainText().simplified().isEmpty())){
        return 1;
    }else{
        return 0;
    }
}

void effectWidget::setFieldsCardSlot(){
    cardWidget::setFieldsCardSlot();
    EffectCards* tmp = dynamic_cast<EffectCards*>(card);
    tmp->setEffectBase(effect->toPlainText().toStdString());
}

