#include "spellwidget.h"


spellWidget::spellWidget(Deck * currDeck,QWidget *parent) : effectWidget(currDeck,parent)
{
    idSpell = -1;
    cardGroup -> setObjectName("cardSpell");


    spellElement.push_back("Earth");
    spellElement.push_back("Fire");
    spellElement.push_back("Water");
    spellElement.push_back("Wind");
    spellElement.push_back("Poison");
    spellElement.push_back("Thunder");
    spellElement.push_back("Ice");
    spellElement.push_back("Time");
    spellElement.push_back("Storm");

    QHBoxLayout *footer = new QHBoxLayout();
    QHBoxLayout *menuIcon = new QHBoxLayout();
    QHBoxLayout *menuIcon2 = new QHBoxLayout();

    spellType = new QLabel();
    title = new QLabel("Seleziona l'elemento della Spell: ");
    spellDmg = new QLineEdit();

    QIntValidator *validator = new QIntValidator();
    validator->setRange(1, 9);

    spellDmg->setValidator(validator);

    air = new ClickableLabel();
    QPixmap airImg("asset/Icon/wind.png");
    air->setPixmap(airImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ground = new ClickableLabel();
    QPixmap groundImg("asset/Icon/earth.png");
    ground->setPixmap(groundImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    flame = new ClickableLabel();
    QPixmap flameImg("asset/Icon/fire.png");
    flame->setPixmap(flameImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

     ocean = new ClickableLabel();
    QPixmap oceanImg("asset/Icon/water.png");
    ocean->setPixmap(oceanImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    storm = new ClickableLabel();
    QPixmap stormImg("asset/Icon/storm.png");
    storm->setPixmap(stormImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    thunder = new ClickableLabel();
    QPixmap thunderImg("asset/Icon/thunder.png");
    thunder->setPixmap(thunderImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    time = new ClickableLabel();
    QPixmap timeImg("asset/Icon/time.png");
    time->setPixmap(timeImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ice = new ClickableLabel();
    QPixmap iceImg("asset/Icon/ice.png");
    ice->setPixmap(iceImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    poison = new ClickableLabel();
    QPixmap poisonImg("asset/Icon/poison.png");
    poison->setPixmap(poisonImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));



    menuIcon->addWidget(ground);
    menuIcon -> setSpacing(25);
    menuIcon->addWidget(flame);
    menuIcon -> setSpacing(25);
    menuIcon->addWidget(ocean);
    menuIcon -> setSpacing(25);
    menuIcon ->addWidget(air);

    menuIcon2->addWidget(poison);
    menuIcon2 -> setSpacing(25);
    menuIcon2->addWidget(ice);
    menuIcon2 -> setSpacing(25);
    menuIcon2->addWidget(time);
    menuIcon2 -> setSpacing(25);
    menuIcon2 ->addWidget(thunder);
    menuIcon2 -> setSpacing(25);
    menuIcon2 ->addWidget(storm);

    footer -> addWidget(spellType);
    footer -> addStretch();
    footer -> addWidget(spellDmg);

    inside ->addStretch();
    inside -> addLayout(footer);

    outsideVertical -> addStretch();
    outsideVertical -> addWidget(title);
     outsideVertical -> addSpacing(10);
    outsideVertical -> addLayout(menuIcon);
    outsideVertical -> addLayout(menuIcon2);
    outsideVertical -> addStretch();
    ground->setFixedSize(72,72);
    flame->setFixedSize(72,72);
    ocean->setFixedSize(72,72);
    air->setFixedSize(72,72);

    time->setFixedSize(72,72);
    thunder->setFixedSize(72,72);
    storm->setFixedSize(72,72);
    poison->setFixedSize(72,72);
    ice->setFixedSize(72,72);
    spellDmg ->setFixedSize(64,64);





    ground->setObjectName("Elements");
    flame->setObjectName("Elements");
    ocean->setObjectName("Elements");
    air->setObjectName("Elements");
    poison->setObjectName("Elements");
    ice->setObjectName("Elements");
    time->setObjectName("Elements");
    thunder->setObjectName("Elements");
    storm->setObjectName("Elements");

    spellDmg -> setObjectName("AttAttr");

    ground->setProperty("id" ,0);
    flame->setProperty("id" ,1);
    ocean->setProperty("id" ,2);
    air->setProperty("id" ,3);
    poison->setProperty("id" ,4);
    thunder->setProperty("id" ,5);
    ice->setProperty("id" ,6);
    time->setProperty("id" ,7);
    storm->setProperty("id" ,8);





    title -> setAlignment(Qt::AlignCenter);
    ground -> setAlignment(Qt::AlignCenter);
    air -> setAlignment(Qt::AlignCenter);
    ocean -> setAlignment(Qt::AlignCenter);
    storm -> setAlignment(Qt::AlignCenter);
    poison -> setAlignment(Qt::AlignCenter);
    time -> setAlignment(Qt::AlignCenter);
    thunder -> setAlignment(Qt::AlignCenter);
    ice -> setAlignment(Qt::AlignCenter);
    flame -> setAlignment(Qt::AlignCenter);
    menuIcon2 -> setAlignment(Qt::AlignCenter);
    menuIcon -> setAlignment(Qt::AlignCenter);
    spellDmg -> setAlignment(Qt::AlignCenter);

    connect(ground, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(air, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(ocean, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(flame, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(poison, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(thunder, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(ice, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(time, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(storm, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);

    spellDmg ->setMaxLength(1);


}


spellWidget::spellWidget(spellCard* s, QWidget *parent) : effectWidget(nullptr, parent){

    card = s;
    idSpell = -1;
    for(unsigned int i = 0 ; i < spellElement.size(); i++){
        if(spellElement[i]==s->getElement()){
        idSpell = i;
        break;
        }
    }
    cardGroup -> setObjectName("cardSpell");


    spellElement.push_back("Earth");
    spellElement.push_back("Fire");
    spellElement.push_back("Water");
    spellElement.push_back("Wind");
    spellElement.push_back("Poison");
    spellElement.push_back("Thunder");
    spellElement.push_back("Ice");
    spellElement.push_back("Time");
    spellElement.push_back("Storm");

    QHBoxLayout *footer = new QHBoxLayout();
    QHBoxLayout *menuIcon = new QHBoxLayout();
    QHBoxLayout *menuIcon2 = new QHBoxLayout();

    spellType = new QLabel();
    title = new QLabel("Seleziona l'elemento della Spell: ");
    spellDmg = new QLineEdit();

    QIntValidator *validator = new QIntValidator();
    validator->setRange(1, 9);

    spellDmg->setValidator(validator);

    air = new ClickableLabel();
    QPixmap airImg("asset/Icon/wind.png");
    air->setPixmap(airImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ground = new ClickableLabel();
    QPixmap groundImg("asset/Icon/earth.png");
    ground->setPixmap(groundImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    flame = new ClickableLabel();
    QPixmap flameImg("asset/Icon/fire.png");
    flame->setPixmap(flameImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

     ocean = new ClickableLabel();
    QPixmap oceanImg("asset/Icon/water.png");
    ocean->setPixmap(oceanImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    storm = new ClickableLabel();
    QPixmap stormImg("asset/Icon/storm.png");
    storm->setPixmap(stormImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    thunder = new ClickableLabel();
    QPixmap thunderImg("asset/Icon/thunder.png");
    thunder->setPixmap(thunderImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    time = new ClickableLabel();
    QPixmap timeImg("asset/Icon/time.png");
    time->setPixmap(timeImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ice = new ClickableLabel();
    QPixmap iceImg("asset/Icon/ice.png");
    ice->setPixmap(iceImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    poison = new ClickableLabel();
    QPixmap poisonImg("asset/Icon/poison.png");
    poison->setPixmap(poisonImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));



    menuIcon->addWidget(ground);
    menuIcon -> setSpacing(25);
    menuIcon->addWidget(flame);
    menuIcon -> setSpacing(25);
    menuIcon->addWidget(ocean);
    menuIcon -> setSpacing(25);
    menuIcon ->addWidget(air);

    menuIcon2->addWidget(poison);
    menuIcon2 -> setSpacing(25);
    menuIcon2->addWidget(ice);
    menuIcon2 -> setSpacing(25);
    menuIcon2->addWidget(time);
    menuIcon2 -> setSpacing(25);
    menuIcon2 ->addWidget(thunder);
    menuIcon2 -> setSpacing(25);
    menuIcon2 ->addWidget(storm);

    footer -> addWidget(spellType);
    footer -> addStretch();
    footer -> addWidget(spellDmg);

    inside ->addStretch();
    inside -> addLayout(footer);

    outsideVertical -> addStretch();
    outsideVertical -> addWidget(title);
    outsideVertical -> addSpacing(10);
    outsideVertical -> addLayout(menuIcon);
    outsideVertical -> addLayout(menuIcon2);
    outsideVertical -> addStretch();
    ground->setFixedSize(72,72);
    flame->setFixedSize(72,72);
    ocean->setFixedSize(72,72);
    air->setFixedSize(72,72);

    time->setFixedSize(72,72);
    thunder->setFixedSize(72,72);
    storm->setFixedSize(72,72);
    poison->setFixedSize(72,72);
    ice->setFixedSize(72,72);
    spellDmg ->setFixedSize(64,64);





    ground->setObjectName("Elements");
    flame->setObjectName("Elements");
    ocean->setObjectName("Elements");
    air->setObjectName("Elements");
    poison->setObjectName("Elements");
    ice->setObjectName("Elements");
    time->setObjectName("Elements");
    thunder->setObjectName("Elements");
    storm->setObjectName("Elements");

    spellDmg -> setObjectName("AttAttr");


    title -> setAlignment(Qt::AlignCenter);
    ground -> setAlignment(Qt::AlignCenter);
    air -> setAlignment(Qt::AlignCenter);
    ocean -> setAlignment(Qt::AlignCenter);
    storm -> setAlignment(Qt::AlignCenter);
    poison -> setAlignment(Qt::AlignCenter);
    time -> setAlignment(Qt::AlignCenter);
    thunder -> setAlignment(Qt::AlignCenter);
    ice -> setAlignment(Qt::AlignCenter);
    flame -> setAlignment(Qt::AlignCenter);
    menuIcon2 -> setAlignment(Qt::AlignCenter);
    menuIcon -> setAlignment(Qt::AlignCenter);

    spellDmg -> setAlignment(Qt::AlignCenter);


    ground->setProperty("id" ,0);
    flame->setProperty("id" ,1);
    ocean->setProperty("id" ,2);
    air->setProperty("id" ,3);
    poison->setProperty("id" ,4);
    thunder->setProperty("id" ,5);
    ice->setProperty("id" ,6);
    time->setProperty("id" ,7);
    storm->setProperty("id" ,8);


    nameCard->setText(QString::fromStdString(s->getName()));
    costCard->setText(QString::number(s->getCost()));
    desc->setText(QString::fromStdString(s->getDescription()));
    spellDmg->setText(QString::number(s->getDamage()));
    effect->setText(QString::fromStdString(s->getEffect()));
    effect -> setAlignment(Qt::AlignCenter);

    std::string element = s->getElement();
    if(element == "Earth"){
        spellType->setPixmap(groundImg);
    }
    else if (element == "Fire"){
        spellType->setPixmap(flameImg);
    }
    else if(element == "Water"){
        spellType->setPixmap(oceanImg);
    }
    else if(element == "Wind"){
        spellType->setPixmap(airImg);
    }
    else if(element == "Poison"){
        spellType->setPixmap(poisonImg);
    }
    else if(element == "Thunder"){
        spellType->setPixmap(thunderImg);
    }
    else if(element == "Ice"){
        spellType->setPixmap(iceImg);
    }
    else if(element == "Time"){
        spellType->setPixmap(timeImg);
    }
    else if(element == "Storm"){
        spellType->setPixmap(stormImg);
    }

    std::string imgPath = s->getUrl();
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

    connect(ground, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(air, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(ocean, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(flame, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(poison, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(thunder, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(ice, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(time, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);
    connect(storm, &ClickableLabel::clicked, this, &spellWidget::onImageClickedSlot);


}



Card* spellWidget::getInput() {
    return  new spellCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(),effect->toPlainText().toStdString(), spellElement[idSpell],spellDmg->text().toInt());;
}



bool spellWidget::checkInput() const{

    if(effectWidget::checkInput() && idSpell != -1 && !(spellDmg ->text().simplified().isEmpty()) ){
        return 1;
    }else{
        return 0;
    }
}
void spellWidget::generate(){


    spellDmg ->setReadOnly(true);
    title ->hide();

    flame ->hide();
    air ->hide();
    ocean ->hide();
    ground ->hide();
    poison ->hide();
    time ->hide();
    ice ->hide();
    storm ->hide();
    thunder ->hide() ;
    effectWidget::generate();
} ;
void spellWidget::onImageClickedSlot(){

    QLabel* tmp = qobject_cast<QLabel*>(sender());
    idSpell = tmp -> property("id").toInt();
    QPixmap image = tmp->pixmap(Qt::ReturnByValue);
    spellType -> setPixmap(image);

}


void spellWidget::setFieldsCardSlot() {
    effectWidget::setFieldsCardSlot();

    spellCard* tmp = dynamic_cast<spellCard*>(card);
    tmp->setDamage(spellDmg->text().toInt());
    tmp->setElement(spellElement[idSpell]);

    takeScreen(tmp);

}
