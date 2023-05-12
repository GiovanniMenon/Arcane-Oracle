#include "cardpage.h"

#include <QFileDialog>




CardPage::CardPage(QWidget * parent) :  QWidget(parent)
{
    main = new QVBoxLayout(this);
    QGroupBox *footerMenu = new QGroupBox();

    QHBoxLayout * header = new QHBoxLayout();
    card = new QHBoxLayout();

    QHBoxLayout * footer = new QHBoxLayout(footerMenu);

    QHBoxLayout * footerCenter = new QHBoxLayout();


    errore = new QLabel();
    backButton = new QPushButton("Back");

    absCard = new QWidget();

    generateButton = new QPushButton("Generate Card");

    saveButton = new QPushButton("Export Png");
    removeButton = new QPushButton("Discard");
    addButton = new QPushButton("Add To Deck");

    saveButton -> hide();
    removeButton -> hide();
    addButton -> hide();



    header->addWidget(backButton);
    header -> addStretch();
    header->addWidget(errore);







    footer -> addStretch();
    footer ->addWidget(removeButton);
    footer -> addStretch();
    footer ->addWidget(saveButton);
    footer ->addWidget(generateButton);
    footer -> addStretch();
    footer ->addWidget(addButton);
    footer -> addStretch();

    footer->setAlignment(Qt::AlignCenter);
    footerCenter->setAlignment(Qt::AlignCenter);
    footerCenter->addWidget(footerMenu);

    main -> addLayout(header);
    main -> addLayout(card);
    main -> addLayout(footerCenter);


    saveButton ->setObjectName("saveButton");
    addButton ->setObjectName("addButton");
    generateButton -> setObjectName("saveButton");
    removeButton ->setObjectName("remButton");



    backButton -> setFixedSize(140, 45);
    saveButton -> setFixedSize(250, 70);
    generateButton -> setFixedSize(250, 70);
    addButton -> setFixedSize(250, 70);
    removeButton -> setFixedSize(250, 70);
    footerMenu -> setFixedWidth(1200);


    connect(generateButton,&QPushButton::clicked, this ,&CardPage::generateCardSlot);
    connect(backButton,&QPushButton::clicked, this ,&CardPage::BackHomePageSlot);
    connect(addButton,&QPushButton::clicked, this ,&CardPage::AddNewCardSlot);
    connect(removeButton,&QPushButton::clicked, this ,&CardPage::RemoveCardSlot);
    connect(saveButton,&QPushButton::clicked, this ,&CardPage::SaveScreenSlot);
}

void CardPage::BackHomePageSlot() {
   dynamic_cast<cardWidget*>(absCard) -> hide();
   emit BackHomePageSignal();
}
void CardPage::generateCardSlot() {

    if(dynamic_cast<cardWidget*>(absCard)->checkInput()){

    addButton ->show();
    removeButton -> show();
    saveButton -> show();

    // chiamiamo il metodo per rimuovere la desc
    // chiamiamo il metodo che displaya l'immagine dentro il rettangolo centrale
    dynamic_cast<cardWidget*>(absCard)->generate();

    backButton -> hide();
    generateButton -> hide();
    errore->clear();
    }else{
        errore -> setText("Non si possono usare nomi di carte gia' utilizzati o lasciare campi della carta vuoti");
    }
}

void CardPage::RemoveCardSlot() {
    ::remove(dynamic_cast<cardWidget*>(absCard) -> getUrl().c_str());
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


