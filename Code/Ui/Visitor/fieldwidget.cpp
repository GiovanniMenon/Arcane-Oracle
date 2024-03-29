#include "fieldwidget.h"

fieldWidget::fieldWidget(Deck * currDeck,QWidget *parent) : effectWidget(currDeck,parent)
{
    id = -1;
    cardGroup -> setObjectName("cardField");

    elements.push_back("Earth");
    elements.push_back("Fire");
    elements.push_back("Water");
    elements.push_back("Wind");

    elementMenu = new QHBoxLayout();
    QHBoxLayout *CenterfieldType = new QHBoxLayout();
    LabelElement = new QLabel("Scegli l'elemento: ");
    fieldType = new QLabel();

    earth = new ClickableLabel();
    QPixmap earthImg("asset/Icon/earth.png");
    earth->setPixmap(earthImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    fire = new ClickableLabel;
    QPixmap fireImg("asset/Icon/fire.png");
    fire->setPixmap(fireImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    water = new ClickableLabel;
    QPixmap waterImg("asset/Icon/water.png");
    water->setPixmap(waterImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    wind = new ClickableLabel;
    QPixmap windImg("asset/Icon/wind.png");
    wind->setPixmap(windImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    earth->setFixedSize(72,72);
    fire->setFixedSize(72,72);
    water->setFixedSize(72,72);
    wind->setFixedSize(72,72);
    fieldType -> setFixedSize(72,72);



    earth->setObjectName("Elements");
    fire->setObjectName("Elements");
    water->setObjectName("Elements");
    wind->setObjectName("Elements");


    elementMenu->addWidget(earth);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(fire);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(water);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(wind);


    earth -> setAlignment(Qt::AlignCenter);
    wind -> setAlignment(Qt::AlignCenter);
    water -> setAlignment(Qt::AlignCenter);
    fire -> setAlignment(Qt::AlignCenter);
    elementMenu -> setAlignment(Qt::AlignCenter);
    LabelElement -> setAlignment(Qt::AlignCenter);
    fieldType -> setAlignment(Qt::AlignCenter);
    CenterfieldType -> setAlignment(Qt::AlignCenter);

    outsideVertical -> addSpacing(100);
    outsideVertical -> addWidget(LabelElement);
    outsideVertical -> addSpacing(15);
    outsideVertical -> addLayout(elementMenu);
    outsideVertical -> addStretch();

    CenterfieldType -> addWidget(fieldType);
    inside -> addLayout(CenterfieldType);
    inside -> addSpacing(15);

    earth->setProperty("id" ,0);
    fire->setProperty("id" ,1);
    water->setProperty("id" ,2);
    wind->setProperty("id" ,3);

    connect(earth, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(wind, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(water, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(fire, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);


}

fieldWidget::fieldWidget(territoryCard* f, QWidget *parent) : effectWidget(nullptr, parent){
    card = f;
    id = -1;
    cardGroup -> setObjectName("cardField");

    elements.push_back("Earth");
    elements.push_back("Fire");
    elements.push_back("Water");
    elements.push_back("Wind");

    for(unsigned int i = 0 ; i < elements.size(); i++){
        if(elements[i]==f->getType()){
        id = i;
        break;
        }
    }
    elementMenu = new QHBoxLayout();
    QHBoxLayout *CenterfieldType = new QHBoxLayout();
    LabelElement = new QLabel("Scegli l'elemento: ");
    fieldType = new QLabel();

    earth = new ClickableLabel();
    QPixmap earthImg("asset/Icon/earth.png");
    earth->setPixmap(earthImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    fire = new ClickableLabel;
    QPixmap fireImg("asset/Icon/fire.png");
    fire->setPixmap(fireImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    water = new ClickableLabel;
    QPixmap waterImg("asset/Icon/water.png");
    water->setPixmap(waterImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    wind = new ClickableLabel;
    QPixmap windImg("asset/Icon/wind.png");
    wind->setPixmap(windImg.scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    earth->setFixedSize(72,72);
    fire->setFixedSize(72,72);
    water->setFixedSize(72,72);
    wind->setFixedSize(72,72);
    fieldType -> setFixedSize(72,72);



    earth->setObjectName("Elements");
    fire->setObjectName("Elements");
    water->setObjectName("Elements");
    wind->setObjectName("Elements");


    elementMenu->addWidget(earth);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(fire);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(water);
    elementMenu -> setSpacing(25);
    elementMenu->addWidget(wind);


    earth -> setAlignment(Qt::AlignCenter);
    wind -> setAlignment(Qt::AlignCenter);
    water -> setAlignment(Qt::AlignCenter);
    fire -> setAlignment(Qt::AlignCenter);
    elementMenu -> setAlignment(Qt::AlignCenter);
    LabelElement -> setAlignment(Qt::AlignCenter);
    fieldType -> setAlignment(Qt::AlignCenter);
    CenterfieldType -> setAlignment(Qt::AlignCenter);

    outsideVertical -> addSpacing(100);
    outsideVertical -> addWidget(LabelElement);
    outsideVertical -> addSpacing(15);
    outsideVertical -> addLayout(elementMenu);
    outsideVertical -> addStretch();

    CenterfieldType -> addWidget(fieldType);
    inside -> addLayout(CenterfieldType);
    inside -> addSpacing(15);

    earth->setProperty("id" ,0);
    fire->setProperty("id" ,1);
    water->setProperty("id" ,2);
    wind->setProperty("id" ,3);

    nameCard->setText(QString::fromStdString(f->getName()));
    costCard->setText(QString::number(f->getCost()));
    desc->setText(QString::fromStdString(f->getDescription()));
    effect->setText(QString::fromStdString(f->getEffect()));

    std::string type = f->getType();
    if(type == "Earth") {
        fieldType->setPixmap(earthImg);
    }
    else if(type == "Fire"){
        fieldType->setPixmap(fireImg);
    }
    else if(type == "Water"){
        fieldType->setPixmap(waterImg);
    }
    else if(type == "Wind"){
        fieldType->setPixmap(windImg);
    }


    std::string imgPath = f->getUrl();
    std::string searchString = "Card";

    size_t lastSlashPos = imgPath.find_last_of('/');
    size_t secondLastSlashPos = imgPath.find_last_of('/', lastSlashPos - 1);
    size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
    size_t index = imgPath.find(searchString, secondLastSlashPos + 1);
    if (index != std::string::npos) {
        imgPath.replace(index, substringLength, "CardImg");
    }

    QPixmap pixmap(QString::fromStdString(imgPath));
    scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel -> setPixmap(scaledPixmap);
    imageLayout-> setContentsMargins(0,0,0,0);
    imageLayout -> addWidget(imageLabel);
    desc->setEnabled(false);
    effect -> setAlignment(Qt::AlignCenter);

    connect(earth, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(wind, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(water, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);
    connect(fire, &ClickableLabel::clicked, this, &fieldWidget::onImageClickedSlot);

}

Card* fieldWidget::getInput() {
    return new territoryCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(),effect->toPlainText().toStdString(), elements[id]);
}


bool fieldWidget::checkInput() const{

    if(effectWidget::checkInput() && id != -1){
        return 1;
    }else{
        return 0;
    }
}
void fieldWidget::generate(){

    wind -> hide();
    earth -> hide();
    fire -> hide();
    water -> hide();
    LabelElement -> hide();
    effectWidget::generate();
} ;
void fieldWidget::onImageClickedSlot(){

    QLabel* tmp = qobject_cast<QLabel*>(sender());
    id = tmp -> property("id").toInt();
    QPixmap image =tmp->pixmap(Qt::ReturnByValue);
    fieldType ->setPixmap(image);
}

void fieldWidget::setFieldsCardSlot(){
    effectWidget::setFieldsCardSlot();
    territoryCard* tmp = dynamic_cast<territoryCard*>(card);
    if(screenshot){
        tmp->setType(elements[id]);

        takeScreen(tmp);
    }
}

void fieldWidget::manual() {
    effectWidget::manual();
    manuale->setWindowTitle("Manuale Mostro");
    QLabel *fieldText = new QLabel(textLabel -> text() + "5)L'elemento della Carta terreno. Gli elementi sono : Terra, Fuoco, Aria, Acqua.\n");
    imageLabelManual -> setPixmap(QPixmap("asset/Manual/fielManual.png"));
    manualLayout->addWidget(fieldText, 0, Qt::AlignLeft);

    manuale->exec();

}
