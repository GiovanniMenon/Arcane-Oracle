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
    outsideVertical -> addStretch();

    spellDmg -> setObjectName("AttAttr");
    durata -> setObjectName("TimeAttr");

    spellDmg ->setMaxLength(1);



    spellDmg ->setFixedSize(64,64);
    durata ->setFixedSize(64,64);


    durata -> setAlignment(Qt::AlignCenter);
    spellDmg -> setAlignment(Qt::AlignCenter);
}

trapWidget::trapWidget(trapCard* t , QWidget *parent) : effectWidget(nullptr, parent){
    card = t;
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
    durata -> setObjectName("HPAttr");



    spellDmg ->setFixedSize(64,64);
    durata ->setFixedSize(72,72);


    durata -> setAlignment(Qt::AlignCenter);
    spellDmg -> setAlignment(Qt::AlignCenter);

    nameCard->setText(QString::fromStdString(t->getName()));
    costCard->setText(QString::number(t->getCost()));
    desc->setText(QString::fromStdString(t->getDescription()));
    effect->setText(QString::fromStdString(t->getEffect()));
    spellDmg->setText(QString::number(t->getDamage()));
    durata->setText(QString::number(t->getDuration()));

    std::string imgPath = t->getUrl();
    std::string searchString = "Card";

    size_t lastSlashPos = imgPath.find_last_of('/');
    size_t secondLastSlashPos = imgPath.find_last_of('/', lastSlashPos - 1);
    size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
    size_t index = imgPath.find(searchString, secondLastSlashPos + 1);
    if (index != std::string::npos) {
        imgPath.replace(index, substringLength, "CardImg");
    }
    effect -> setAlignment(Qt::AlignCenter);
    QPixmap pixmap(QString::fromStdString(imgPath));
    scaledPixmap = pixmap.scaled(QSize(290,290), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel -> setPixmap(scaledPixmap);

    imageLayout -> addWidget(imageLabel);
    desc->setEnabled(false);
    imageLayout-> setContentsMargins(0,0,0,0);
}

Card* trapWidget::getInput() {
    return new trapCard(nameCard->text().toStdString(),descText.toStdString(),path,costCard->text().toInt(),effect->toPlainText().toStdString() ,spellDmg -> text().toInt(),durata->text().toInt());
}

void trapWidget::generate(){


    spellDmg -> setReadOnly(true);
    durata -> setReadOnly(true);

    effectWidget::generate();
} ;
bool trapWidget::checkInput() const{

    if(effectWidget::checkInput() && !(spellDmg ->text().simplified().isEmpty()) && !(durata ->text().simplified().isEmpty())){
        return 1;
    }else{
        return 0;
    }
}

void trapWidget::setFieldsCardSlot(){
    effectWidget::setFieldsCardSlot();
    trapCard* tmp = dynamic_cast<trapCard*>(card);
    if(screenshot){
    tmp->setDuration(durata->text().toUInt());
    tmp->setDamage(spellDmg->text().toUInt());
    takeScreen(tmp);
    }
}

void trapWidget::manual() {
    effectWidget::manual();
    manuale->setWindowTitle("Manuale Mostro");
    QLabel *trapText = new QLabel(textLabel -> text() + "5)I punti danno della Carta Trappola.\n7)La durata dell'effetto della carta");
    imageLabelManual -> setPixmap(QPixmap("asset/Manual/trapManual.png"));
    manualLayout->addWidget(trapText, 0, Qt::AlignLeft);

    manuale->exec();

}
