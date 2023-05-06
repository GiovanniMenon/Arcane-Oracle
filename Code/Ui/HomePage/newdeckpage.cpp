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
     DeckName = new QLineEdit("Ciao");


     Titlelayout -> addWidget(backButton);
     Titlelayout -> addStretch();

     Button1 -> addStretch();
     Button1 -> addWidget(DeckName);
     Button1 -> addStretch();

     Button2 -> addStretch();
     Button2 -> addWidget(createButton);
     Button2 -> addStretch();

     layout -> addLayout(Titlelayout);
     layout -> addSpacing(100);
     layout -> addWidget(title);
     layout -> addSpacing(80);
     layout -> addWidget(text);
     layout -> addSpacing(40);
     layout -> addLayout(Button1);
     layout -> addSpacing(150);
     layout -> addLayout(Button2);

     layout -> addStretch();

     title -> setAlignment(Qt::AlignCenter);
     text -> setAlignment(Qt::AlignCenter);
     DeckName -> setAlignment(Qt::AlignCenter);
     DeckName -> setFixedSize(450, 80);
     createButton -> setFixedSize(200, 70);
     backButton -> setFixedSize(150, 65);
     createButton->setStyleSheet("QPushButton { border: 2px solid #555555; border-radius: 15px; } QPushButton:hover { background-color: #555555; color: #ffffff; }");



     connect(backButton,&QPushButton::clicked, this ,&NewDeckPage::BackHomePageSlot);

     connect(createButton,&QPushButton::clicked, this ,&NewDeckPage::HomeDeckPageSlot);






}

void NewDeckPage::BackHomePageSlot() {
    layout ->removeWidget(Errore);
    emit BackHomePageSignal();
}

void NewDeckPage::HomeDeckPageSlot() {
    QString NomeDeck = DeckName->text();
    if(Deck::verifyInput(NomeDeck.toStdString()) || Deck::verifyDeckName(NomeDeck.toStdString())){
        Errore = new QLabel ("Sono Presenti Caratteri non riconosciuti o Esiste un Deck gia' un Deck con questo nome");
        layout -> addWidget(Errore);
    }
    else {
        emit HomeDeckPageSignal();
        emit newDeckCreatedSignal(NomeDeck);
}

}

