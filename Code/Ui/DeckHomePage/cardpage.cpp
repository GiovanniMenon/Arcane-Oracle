#include "cardpage.h"
#include "../Visitor/visitor.h"

#include <QDebug>
CardPage::CardPage(QWidget * parent) :  QWidget(parent)
{
    main = new QVBoxLayout(this);
    card = new QHBoxLayout();

    QGroupBox *footerMenu = new QGroupBox();
    QHBoxLayout * header = new QHBoxLayout();
    QHBoxLayout * footer = new QHBoxLayout(footerMenu);
    QHBoxLayout * footerCenter = new QHBoxLayout();


    errore = new QLabel();
    backButton = new QPushButton("Back");

    absCard = new QWidget();

    generateButton = new QPushButton("Generate Card");

    saveButton = new QPushButton("Export Png");
    removeButton = new QPushButton("Discard");
    addButton = new QPushButton("Add To Deck");
    CardManual = new QPushButton("Guide");

    saveButton -> hide();
    removeButton -> hide();
    addButton -> hide();



    header->addWidget(backButton);
    header -> addStretch();
    header->addWidget(errore);
    header -> addStretch();
    header->addWidget(CardManual);

    footer -> addStretch();
    footer ->addWidget(removeButton);
    footer -> addStretch();
    footer ->addWidget(saveButton);
    footer ->addWidget(generateButton);
    footer -> addStretch();
    footer ->addWidget(addButton);
    footer -> addStretch();

    footer->setAlignment(Qt::AlignCenter);
    errore ->setAlignment(Qt::AlignCenter);
    footerCenter->setAlignment(Qt::AlignCenter);
    footerCenter->addWidget(footerMenu);

    main -> addLayout(header);
    main -> addLayout(card);
    main -> addLayout(footerCenter);


    saveButton ->setObjectName("saveButton");
    addButton ->setObjectName("addButton");
    generateButton -> setObjectName("saveButton");
    removeButton ->setObjectName("remButton");


    CardManual-> setFixedSize(140, 45);

    backButton -> setFixedSize(140, 45);
    saveButton -> setFixedSize(250, 70);
    generateButton -> setFixedSize(250, 70);
    addButton -> setFixedSize(250, 70);
    removeButton -> setFixedSize(250, 70);
    footerMenu -> setMinimumWidth(1200);


    connect(generateButton,&QPushButton::clicked, this ,&CardPage::generateCardSlot);
    connect(backButton,&QPushButton::clicked, this ,&CardPage::BackHomePageSlot);
    connect(addButton,&QPushButton::clicked, this ,&CardPage::AddNewCardSlot);
    connect(removeButton,&QPushButton::clicked, this ,&CardPage::RemoveCardSlot);
    connect(saveButton,&QPushButton::clicked, this ,&CardPage::SaveScreenSlot);
    connect(CardManual,&QPushButton::clicked, this ,&CardPage::ManualScreeSlot);




}
void CardPage::ManualScreeSlot() {
   dynamic_cast<cardWidget*>(absCard) -> manual();
}

void CardPage::BackHomePageSlot() {
   disconnect(generateButton, &QPushButton::clicked, this, &CardPage::BackHomePageSlot);
   disconnect(generateButton, &QPushButton::clicked, dynamic_cast<cardWidget*>(absCard), &cardWidget::setFieldsCardSlot);
   disconnect(generateButton, &QPushButton::clicked, this, &CardPage::RefreshImageSlot);
   disconnect(generateButton, &QPushButton::clicked, this, &CardPage::SaveDeckAfterModifySlot);
   connect(generateButton,&QPushButton::clicked, this ,&CardPage::generateCardSlot);
   generateButton->setText("Generate Card");
   dynamic_cast<cardWidget*>(absCard) -> hide();
   emit BackHomePageSignal();
}
void CardPage::generateCardSlot() {

    if(dynamic_cast<cardWidget*>(absCard)->checkInput()){

    addButton ->show();
    removeButton -> show();
    saveButton -> show();
    addButton -> setEnabled(false);
    removeButton -> setEnabled(false);
    saveButton -> setEnabled(false);

    dynamic_cast<cardWidget*>(absCard) -> generate();


    backButton -> hide();
    generateButton -> hide();
    errore->clear();
    }else{
        errore -> setText("Nome della Carta gia' in uso (anche in una carta salvata) oppure alcuni Caratteri non sono accettati.\n Tutti i Campi devono essere riempiti");
    }
}

void CardPage::ErrorSlot(std::string res){
    errore -> setText(QString::fromStdString(res));
}
void CardPage::RemoveCardSlot() {
    std::string imgPath = dynamic_cast<cardWidget*>(absCard) -> getUrl();
    std::string searchString = "Card";

    size_t lastSlashPos = imgPath.find_last_of('/');
    size_t secondLastSlashPos = imgPath.find_last_of('/', lastSlashPos - 1);
    size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
    size_t index = imgPath.find(searchString, secondLastSlashPos + 1);
    if (index != std::string::npos) {
        imgPath.replace(index, substringLength, "CardImg");
        ::remove(imgPath.c_str());
    }
    dynamic_cast<cardWidget*>(absCard) -> hide();
    backButton -> show();
    addButton ->hide();
    removeButton -> hide();
    saveButton -> hide();

    generateButton -> show();
    delete dynamic_cast<cardWidget*>(absCard);
    emit BackBackHomePageSignal();
}
void CardPage::NewCardIdSlot(Deck* currDeck,QWidget* obj) {
    deck = currDeck;
    absCard = dynamic_cast<cardWidget*>(obj);
    card -> addWidget(absCard);
    dynamic_cast<cardWidget*>(absCard) -> show();
    QObject::connect(dynamic_cast<cardWidget*>(obj) , &cardWidget::generateFinishSignal, this, &CardPage::onGenerateCardFinish);
    QObject::connect(dynamic_cast<cardWidget*>(obj) , &cardWidget::signalErrorSignal, this, &CardPage::ErrorSlot);
}
void CardPage::onGenerateCardFinish() {
    addButton -> setEnabled(true);
    removeButton -> setEnabled(true);
    saveButton -> setEnabled(true);
}
void CardPage::SaveScreenSlot() {
   clearFocus();
   QString fileName = QFileDialog::getSaveFileName(this, tr("Salva immagine"), "", tr("Immagini (*.png *.jpg *.bmp)"));
   if(!fileName.isEmpty()){
               QPixmap pixmap = dynamic_cast<cardWidget*>(absCard)->takeScreen(false);
               pixmap.save(fileName);
    }

}

void CardPage::AddNewCardSlot() {
    clearFocus();
    backButton -> show();
    addButton ->hide();
    removeButton -> hide();
    saveButton -> hide();
    generateButton -> show();
    dynamic_cast<cardWidget*>(absCard) -> hide();
    deck -> insert(dynamic_cast<cardWidget*>(absCard)->getInput());
    deck->save();
    dynamic_cast<cardWidget*>(absCard)->takeScreen(true);
    delete dynamic_cast<cardWidget*>(absCard);
    emit BackBackHomePageSignal();

}

void CardPage::setCard(Card* card){
    c = card;
}

void CardPage::ModifyCardSlot(Card* toModify){
    setCard(toModify);
    Visitor* v = new Visitor();
    c->accept(v);
    absCard = dynamic_cast<cardWidget*>(v->getWidget());
    card -> addWidget(absCard);
    generateButton->setText("Modify Card");

    disconnect(generateButton, &QPushButton::clicked, this,&CardPage::generateCardSlot );
    connect(generateButton, &QPushButton::clicked, dynamic_cast<cardWidget*>(absCard), &cardWidget::setFieldsCardSlot);
    connect(generateButton, &QPushButton::clicked, this, &CardPage::SaveDeckAfterModifySlot);

    connect(generateButton, &QPushButton::clicked, this, &CardPage::RefreshImageSlot);
    connect(generateButton, &QPushButton::clicked, this, &CardPage::BackHomePageSlot);
    emit ModifiedCardSignal();
    emit refreshImageModifiedSignal(toModify);

}

void CardPage::BackShowDeckPageSlot(){
    emit BackShowDeckPageSignal();
}


void CardPage::SaveDeckAfterModifySlot(){
    emit saveDeckAfterModifySignal();
}

void CardPage::RefreshImageSlot(){
    emit refreshImageModifiedSignal(c);
}
