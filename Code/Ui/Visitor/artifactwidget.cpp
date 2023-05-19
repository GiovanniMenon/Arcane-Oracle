#include "artifactwidget.h"


artifactWidget::artifactWidget(Deck * currDeck,QWidget *parent) : cardWidget(currDeck,parent)
{
    artifactType.push_back("Armor");
    artifactType.push_back("Potions");
    artifactType.push_back("Weapon");

    id = -1;
    cardGroup ->setObjectName("cardArtifact");

    cardAtt = new QLineEdit();
    QHBoxLayout *center = new QHBoxLayout();
    artType = new QLabel();
    title = new QLabel("Seleziona il tipo del tuo artefatto: ");
    artTypeText = new QLabel();
    cardDef = new QLineEdit();

    QHBoxLayout *arcType = new QHBoxLayout();
    QHBoxLayout *footer = new QHBoxLayout();

    QIntValidator *validator = new QIntValidator();

    armor = new ClickableLabel;
    QPixmap armorImg("asset/Icon/armor.png");
    armor->setPixmap(armorImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    potions = new ClickableLabel;
    QPixmap potionsImg("asset/Icon/potions.png");
    potions->setPixmap(potionsImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    magic = new ClickableLabel;
    QPixmap magicImg("asset/Icon/magic.png");
    magic->setPixmap(magicImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    arcType->addWidget(armor);
    arcType->addWidget(potions);
    arcType->addWidget(magic);
    validator->setRange(1, 9);

    cardAtt->setValidator(validator);
    cardDef->setValidator(validator);


    footer -> addWidget(cardDef);
    footer -> addStretch();
    footer -> addWidget(cardAtt);

    inside -> addStretch();
    inside -> addWidget(artTypeText);
    artTypeText -> setAlignment(Qt::AlignCenter);
    center -> setAlignment(Qt::AlignCenter);
    title-> setAlignment(Qt::AlignCenter);
    center -> addWidget(artType);
    inside -> addStretch();
    inside -> addLayout(center);
    inside -> addLayout(footer);

    outsideVertical ->addStretch();
    outsideVertical ->addWidget(title);
    outsideVertical ->addLayout(arcType);
    outsideVertical ->addStretch();


    cardAtt -> setObjectName("AttAttr");

    cardDef -> setObjectName("DefAttr");
    magic -> setObjectName("Elements");
    potions -> setObjectName("Elements");
    armor -> setObjectName("Elements");
    artTypeText-> setObjectName("cardEffTitle");

    cardAtt ->setFixedSize(64,64);
    cardDef ->setFixedSize(48,48);
    armor ->setFixedSize(72,72);
    potions ->setFixedSize(72,72);
    magic ->setFixedSize(72,72);

    cardAtt -> setAlignment(Qt::AlignCenter);
    cardDef -> setAlignment(Qt::AlignCenter);
    arcType -> setAlignment(Qt::AlignCenter);
    armor -> setAlignment(Qt::AlignCenter);
    potions -> setAlignment(Qt::AlignCenter);
    magic -> setAlignment(Qt::AlignCenter);

    armor->setProperty("id" ,0);
    potions->setProperty("id" ,1);
    magic->setProperty("id" ,2);

    connect(armor, &ClickableLabel::clicked, this, &artifactWidget::onImageClickedSlot);
    connect(potions, &ClickableLabel::clicked, this, &artifactWidget::onImageClickedSlot);
    connect(magic, &ClickableLabel::clicked, this, &artifactWidget::onImageClickedSlot);


    cardAtt ->setMaxLength(1);
    cardDef ->setMaxLength(1);

}

Card* artifactWidget::getInput() {
    return new artifactCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(),artifactType[id],cardAtt->text().toInt(),cardDef->text().toInt());
}


bool artifactWidget::checkInput() const{

    if(cardWidget::checkInput() && !(cardAtt ->text().simplified().isEmpty()) && !(cardDef ->text().simplified().isEmpty()) && id!=-1){
        return 1;
    }else{
        return 0;
    }
}

void artifactWidget::onImageClickedSlot(){
    QLabel* tmp = qobject_cast<QLabel*>(sender());
    id = tmp -> property("id").toInt();
    QPixmap image = tmp->pixmap();
    artType ->setPixmap(image);
    artTypeText -> setText(QString::fromStdString(artifactType[id]));

}

void artifactWidget::generate(){
    armor  -> hide();
    potions -> hide();
    magic -> hide();
    title -> hide();
    cardAtt -> setReadOnly(true);
    cardDef -> setReadOnly(true);
    cardWidget::generate();
} ;
