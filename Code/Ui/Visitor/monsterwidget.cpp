#include "monsterwidget.h"




monsterWidget::monsterWidget(Deck * currDeck,QWidget *parent) : cardWidget(currDeck,parent)
{
    id = 0;
    cardGroup ->setObjectName("cardMonster");

    cardAtt = new QLineEdit();
    cardHP = new QLineEdit();
    cardDef = new QLineEdit();

    level = new QSpinBox();
    levelIcon = new QGroupBox();
    iconLayout = new QHBoxLayout(levelIcon);

    levelTitle = new QLabel("Inserire il Livello della Carta");
    QHBoxLayout *footer = new QHBoxLayout();
    QHBoxLayout *centerLevelOutside = new QHBoxLayout();

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
    inside -> addWidget(levelIcon);
    inside -> addStretch();
    inside -> addLayout(footer);


    cardAtt -> setObjectName("AttAttr");
    cardHP -> setObjectName("HPAttr");
    cardDef -> setObjectName("DefAttr");

    centerLevelOutside -> setAlignment(Qt::AlignCenter);
    levelTitle -> setAlignment(Qt::AlignCenter);
    centerLevelOutside -> addWidget(level);

    outsideVertical -> addStretch();
    outsideVertical -> addWidget(levelTitle);
    outsideVertical -> addLayout(centerLevelOutside);
    outsideVertical -> addStretch();


    level -> setObjectName("level");
    levelIcon -> setObjectName("levelIcon");



    level -> setMaximum(8);
    level -> setMinimum(1);

    cardAtt ->setFixedSize(64,64);
    cardHP ->setFixedSize(72,72);
    cardDef ->setFixedSize(48,48);
    level ->setFixedSize(60,48);
    levelIcon ->setFixedHeight(35);

    cardAtt ->setMaxLength(1);
    cardHP ->setMaxLength(1);
    cardDef ->setMaxLength(1);

    cardAtt -> setAlignment(Qt::AlignCenter);
    cardHP -> setAlignment(Qt::AlignCenter);
    cardDef -> setAlignment(Qt::AlignCenter);
    centerLevelOutside -> setAlignment(Qt::AlignCenter);
    levelTitle -> setAlignment(Qt::AlignCenter);
    level -> setAlignment(Qt::AlignCenter);
    levelIcon -> setAlignment(Qt::AlignCenter);

    connect(level, QOverload<int>::of(&QSpinBox::valueChanged), this, &monsterWidget::levelSlot);

    iconLayout -> setContentsMargins(0,0,0,0);

}

monsterWidget::monsterWidget(monsterCard* m, QWidget *parent) : cardWidget(nullptr, parent){
    card = m;
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


    cardAtt->setText(QString::number(m->getDamage()));
    cardHP->setText(QString::number(m->getHealth()));
    cardDef->setText(QString::number(m->getDefense()));
    nameCard->setText(QString::fromStdString(m->getName()));
    costCard->setText(QString::number(m->getCost()));
    desc->setText(QString::fromStdString(m->getDescription()));

    std::string imgPath = m->getUrl();
    std::string searchString = "Card";

    size_t index = imgPath.find(searchString);
    if (index != std::string::npos) {
            imgPath.replace(index, searchString.length(), "CardImg");
        }
    QPixmap pixmap(QString::fromStdString(imgPath));
    scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel -> setPixmap(scaledPixmap);

    imageLayout -> addWidget(imageLabel);
    desc->setEnabled(false);
    imageLayout-> setContentsMargins(0,0,0,0);



}


void monsterWidget::levelSlot(int value){

    if(value != 0 && value != 9){

        while (QLayoutItem* item = iconLayout->takeAt(value)) {
            if (QWidget* widget = item->widget()) {
                iconLayout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }

        for(int i=0; i<value-id ; i++){
            QLabel *tmp = new QLabel();
            QPixmap Img("asset/Icon/star.png");
            tmp-> setPixmap(Img.scaled(QSize(24, 24), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            iconLayout ->addWidget(tmp);
            tmp ->setFixedSize(24,24);
        }
        id=value;
    }

}

Card* monsterWidget::getInput() {
    return new monsterCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(), level->value(),cardHP->text().toInt(),cardAtt->text().toInt(), cardDef->text().toInt());
}

void monsterWidget::generate(){

    cardAtt -> setReadOnly(true);
    cardDef -> setReadOnly(true);
    cardHP -> setReadOnly(true);
    level ->hide();
    levelTitle ->hide();
    cardWidget::generate();
} ;

bool monsterWidget::checkInput() const{

    if(!(level->text().isEmpty()) && cardWidget::checkInput() && !(cardAtt ->text().simplified().isEmpty()) && !(cardDef ->text().simplified().isEmpty()) && !(cardHP ->text().simplified().isEmpty())){
        return 1;
    }else{
        return 0;
    }
}

void monsterWidget::setFieldsCardSlot(){
    cardWidget::setFieldsCardSlot();
    monsterCard* tmp = dynamic_cast<monsterCard*>(card);
    tmp->setDamage(cardAtt->text().toUInt());
    tmp->setDefense(cardDef->text().toUInt());
    tmp->setHealth(cardHP->text().toUInt());


    takeScreen(tmp);

}

void monsterWidget::manual() {



    manuale->setWindowTitle("Manuale Mostro");
    QLabel *monsterText = new QLabel(textLabel -> text() + "4)Il Livello del mostro, da 1 a 8. 5)I punti di Attacco del mostro.\n6)I punti Difesa o Armatura. \n7)I Punti Vita del mostro.");
    imageLabelManual -> setPixmap(QPixmap("asset/Manual/monsterManual.png"));
    manualLayout->addWidget(monsterText, 0, Qt::AlignLeft);

    manuale->exec();


}
