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
     QLabel *title = new QLabel("Create your Own Deck");
     QLabel *text = new QLabel("Enter the name of your deck");
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
     layout -> addSpacing(150);
     layout -> addLayout(Button2);

     layout -> addStretch();

     title -> setAlignment(Qt::AlignCenter);
     text -> setAlignment(Qt::AlignCenter);
     DeckName -> setAlignment(Qt::AlignCenter);
     DeckName -> setFixedSize(450, 80);
     createButton -> setFixedSize(250, 70);
     backButton -> setFixedSize(150, 60);




     connect(backButton,&QPushButton::clicked, this ,&NewDeckPage::BackHomePageSlot);

     connect(createButton,&QPushButton::clicked, this ,&NewDeckPage::HomeDeckPageSlot);






}

void NewDeckPage::BackHomePageSlot() {
    layout ->removeWidget(Errore);
    emit BackHomePageSignal();
}

void NewDeckPage::HomeDeckPageSlot() {
    QString NomeDeck = DeckName->text();
    if(Deck::verifyInput(NomeDeck.toStdString()) || Deck::verifyDeckName(NomeDeck.toStdString()) || NomeDeck.isEmpty() ){
        Errore = new QLabel ("Sono Presenti Caratteri non riconosciuti o Esiste un Deck gia' un Deck con questo nome");
        layout -> addWidget(Errore);
    }
    else {
        emit HomeDeckPageSignal();
        emit newDeckCreatedSignal(NomeDeck);
}

}

