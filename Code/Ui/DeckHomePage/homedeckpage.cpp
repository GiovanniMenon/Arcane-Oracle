#include "homedeckpage.h"
#include <QLabel>


HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QVBoxLayout(this);
    QHBoxLayout * Head = new QHBoxLayout();
    QHBoxLayout * Box = new QHBoxLayout();

    nome1 = new QLabel();

    QPushButton * backButton = new QPushButton("EXIT");
    QPushButton * ShowDeck = new QPushButton("Show Deck");
    QPushButton * GenerateCard = new QPushButton("Generate Card");

    ButtonMenu = new QGroupBox();
    LastCard = new QGroupBox();
    ButtonMenu->setStyleSheet("QGroupBox { border: 2px solid;border-radius: 10px; }");
    LastCard->setStyleSheet("QGroupBox { border: 2px solid revoid BackDeckPageSlot();border-radius: 10px; }");


    QVBoxLayout * BoxVertical = new QVBoxLayout(ButtonMenu);


    BoxVertical -> addStretch();
    BoxVertical -> addWidget(ShowDeck);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(GenerateCard);
    BoxVertical -> addStretch();
    BoxVertical -> setAlignment(Qt::AlignCenter);

    ButtonMenu -> setLayout(BoxVertical);
    Box -> addSpacing(25);
    Box -> addWidget(ButtonMenu);
    Box -> addStretch();
    Box -> addWidget(LastCard);
    Box -> addStretch();

    Head -> addSpacing(25);
    Head -> addWidget(backButton);
    Head -> addStretch();
    Head -> addStretch();
    Head -> addWidget(nome1);
    Head -> setAlignment(Qt::AlignCenter);
    Head -> addStretch();


    layout -> addLayout(Head);
    layout -> addStretch();
    layout -> addLayout(Box);
    layout -> addStretch();

    backButton -> setFixedSize(155, 60);
    ShowDeck -> setFixedSize(250, 70);
    GenerateCard-> setFixedSize(250, 70);
    ButtonMenu -> setFixedSize(350, 600);
    LastCard -> setFixedSize(350, 600);

    connect(backButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
    connect(GenerateCard,&QPushButton::clicked,this , &HomeDeckPage::GenerateCardSlot);
    connect(ShowDeck, &QPushButton::clicked, this, &HomeDeckPage::ShowDeckSlot);



}

void HomeDeckPage::GenerateCardSlot() {
    emit GenerateCardSignal();
}

void HomeDeckPage::BackHomePageSlot() {
    deck.clear(); //pulisco il mazzo da quello precedente
    emit BackHomePageSignal();
}

void HomeDeckPage::newDeckCreatedSlot(QString nomeDeck) {
    nome1 -> setText(nomeDeck);
    deck.SetDeck(nomeDeck.toStdString());
}

void HomeDeckPage::ShowDeckSlot() {
    emit ShowDeckSignal();
    emit DeckSelectedSignal(&deck);
}

