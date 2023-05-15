#include "homedeckpage.h"
#include <QLabel>


HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QHBoxLayout(this);
    ButtonMenu = new QGroupBox();
    LastCard = new QGroupBox();

    QVBoxLayout *col = new QVBoxLayout();
    QVBoxLayout * BoxVertical = new QVBoxLayout(ButtonMenu);
    lastCardLayout = new QVBoxLayout(LastCard);
    QHBoxLayout * Exit = new QHBoxLayout();

    header = new QLabel();
    header-> setAlignment(Qt::AlignCenter);
    header -> setObjectName("Title");
    imageLabel = new QLabel();
    stillNoCard = new QLabel();
    QPushButton * ExitButton = new QPushButton("EXIT");
    QPushButton * ShowDeck = new QPushButton("Show Deck");
    QPushButton * GenerateCard = new QPushButton("Generate Card");
    ExitButton ->setObjectName("ExitButton");
    ShowDeck -> setObjectName("funButton");
    GenerateCard -> setObjectName("funButton");
    ButtonMenu ->setObjectName("ButtonGroupHomeDeck");






    Exit -> addWidget(ExitButton);
    Exit -> setAlignment(Qt::AlignCenter);
    LastCard -> setAlignment(Qt::AlignCenter);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(ShowDeck);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(GenerateCard);
    BoxVertical -> addStretch();
    BoxVertical -> addLayout(Exit);
    BoxVertical -> addSpacing(20);
    BoxVertical -> setAlignment(Qt::AlignCenter);


    ButtonMenu -> setLayout(BoxVertical);


    col->addWidget(header);
    col->addStretch();
    col->addWidget(LastCard);
    col->addStretch();
    col ->setAlignment(Qt::AlignCenter);

    layout -> addSpacing(50);
    layout -> addWidget(ButtonMenu);
    layout -> addStretch();
    layout -> addLayout(col);
    layout -> addSpacing(50);


    ExitButton -> setFixedSize(155, 60);
    ShowDeck -> setFixedSize(260, 80);
    GenerateCard-> setFixedSize(260, 80);
    ButtonMenu -> setFixedSize(400, 750);
    LastCard -> setFixedSize(390, 625);

    connect(ExitButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
    connect(GenerateCard,&QPushButton::clicked,this , &HomeDeckPage::GenerateCardSlot);
    connect(ShowDeck, &QPushButton::clicked, this, &HomeDeckPage::ShowDeckSlot);



}
void HomeDeckPage::lastCardGenerate() const {
    QVBoxLayout *centerImage = new QVBoxLayout();

    lastCardLayout ->setAlignment(Qt::AlignCenter);
    centerImage ->setAlignment(Qt::AlignCenter);
    if(!deck.is_empty()){
            imageLabel -> setText("");
            stillNoCard -> hide();
            QPixmap lastCard = (QString::fromStdString(deck.last()->getUrl()));
            imageLabel ->setPixmap(lastCard);


    }else{
            stillNoCard -> show();
            imageLabel ->setText("˙◠˙" );
            stillNoCard ->setText("The Deck is Empty");
            imageLabel->setObjectName("Title");
            stillNoCard->setObjectName("GHeader");
            imageLabel ->setAlignment(Qt::AlignCenter);
            stillNoCard ->setAlignment(Qt::AlignCenter);
    }
    centerImage ->addWidget(imageLabel);
    centerImage ->addWidget(stillNoCard);
    lastCardLayout ->addLayout(centerImage);
    lastCardLayout -> setContentsMargins(0,0,0,0);
    centerImage-> setContentsMargins(0,0,0,0);
}

void HomeDeckPage::GenerateCardSlot() {
    emit DeckSelectedSignal(&deck);
    emit GenerateCardSignal();

}

void HomeDeckPage::BackHomePageSlot() {
    deck.clear(); //pulisco il mazzo da quello precedente
    emit BackHomePageSignal();

}

void HomeDeckPage::newDeckCreatedSlot(QString nomeDeck) {

    deck.SetDeck(nomeDeck.toStdString());
    header -> setText(QString::fromStdString(deck.getName()));

    lastCardGenerate();
}

void HomeDeckPage::ShowDeckSlot() {
    emit ShowDeckSignal();
    emit DeckSelectedSignal(&deck);
    //emit ClearShowDeckPageSignal();

}

