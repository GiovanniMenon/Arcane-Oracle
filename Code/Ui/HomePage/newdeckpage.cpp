#include "newdeckpage.h"
#include "../../class/Deck/deck.h"
#include <QPushButton>


#include <iostream>
NewDeckPage::NewDeckPage(QWidget *parent) :  QWidget(parent)
{
     layout  = new QVBoxLayout(this);
     QHBoxLayout * Titlelayout = new QHBoxLayout();
     QHBoxLayout * Button1 = new QHBoxLayout();
     QHBoxLayout * Button2 = new QHBoxLayout();

     QPushButton *backButton = new QPushButton("Back");
     QPushButton *createButton = new QPushButton("Create");
     Errore = new QLabel();

     QLabel *title = new QLabel("Create your Own Deck");
     QLabel *text = new QLabel("Enter the name of your deck");
     QLabel *noChar = new QLabel("Caratteri non validi : '$' , '\\' , '/'");

     title -> setObjectName("Title");
     text -> setObjectName("TextNewDeck");

     DeckName = new QLineEdit();
     DeckName-> setPlaceholderText("(example) Caso Giocattolo");


     Titlelayout -> addWidget(backButton);
     Titlelayout -> addStretch();

     Button1 -> addStretch();
     Button1 -> addWidget(DeckName);
     Button1 -> addStretch();

     Button2 -> addStretch();
     Button2 -> addWidget(createButton);
     Button2 -> addStretch();

     layout -> addLayout(Titlelayout);
     layout -> addSpacing(80);
     layout -> addWidget(title);
     layout -> addSpacing(30);
     layout -> addWidget(text);
     layout -> addSpacing(10);
     layout -> addLayout(Button1);
     layout -> addWidget(noChar);
     layout -> addSpacing(150);
     layout -> addLayout(Button2);

     layout -> addStretch();
     layout -> addWidget(Errore);
     Errore -> setAlignment(Qt::AlignCenter);
     noChar-> setAlignment(Qt::AlignCenter);
     title -> setAlignment(Qt::AlignCenter);
     text -> setAlignment(Qt::AlignCenter);
     DeckName -> setAlignment(Qt::AlignCenter);
     DeckName -> setFixedSize(450, 80);
     createButton -> setFixedSize(250, 70);
     backButton -> setFixedSize(150, 60);

     DeckName -> setMaxLength(16);

     connect(backButton,&QPushButton::clicked, this ,&NewDeckPage::BackHomePageSlot);
     connect(createButton,&QPushButton::clicked, this ,&NewDeckPage::HomeDeckPageSlot);






}

void NewDeckPage::BackHomePageSlot() {
    Errore -> setText("");
    emit BackHomePageSignal();
}

void NewDeckPage::HomeDeckPageSlot() {
    QString NomeDeck = DeckName->text();
    if(Deck::verifyInput(NomeDeck.toStdString()) || Deck::verifyDeckName(NomeDeck.toStdString()) || NomeDeck.isEmpty() ){
        Errore -> setText ("Sono Presenti Caratteri non validi o esiste gia' un Deck con questo nome o Il campo e' vuoto");
    }
    else {
        emit HomeDeckPageSignal();
        emit newDeckCreatedSignal(NomeDeck);
}

}

