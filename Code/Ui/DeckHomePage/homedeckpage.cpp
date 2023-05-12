#include "homedeckpage.h"
#include <QLabel>


HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QHBoxLayout(this);
    ButtonMenu = new QGroupBox();
    LastCard = new QGroupBox();

    QVBoxLayout *col = new QVBoxLayout();
    QVBoxLayout * BoxVertical = new QVBoxLayout(ButtonMenu);
    QHBoxLayout * Exit = new QHBoxLayout();

    header = new QLabel();
    header-> setAlignment(Qt::AlignCenter);
    header -> setObjectName("Title");

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
    LastCard -> setFixedSize(370, 600);

    connect(ExitButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
    connect(GenerateCard,&QPushButton::clicked,this , &HomeDeckPage::GenerateCardSlot);
    connect(ShowDeck, &QPushButton::clicked, this, &HomeDeckPage::ShowDeckSlot);



}
void HomeDeckPage::lastCardGenerate() const {
    if(!deck.is_empty()){

    }

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
}

