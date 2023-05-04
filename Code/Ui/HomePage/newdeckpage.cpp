#include "newdeckpage.h"
#include "../../class/Deck/deck.h"
#include <QPushButton>
#include <QLabel>

#include <iostream>
NewDeckPage::NewDeckPage(QWidget *parent) :  QWidget(parent)
{
     layout  = new QVBoxLayout(this);
     QHBoxLayout * Titlelayout = new QHBoxLayout();

     QPushButton *backButton = new QPushButton("Back");
     QPushButton *createButton = new QPushButton("Create");
     QLabel *title = new QLabel("Create your Own Deck");
     QLabel *text = new QLabel("Enter the name of your deck");
     DeckName = new QLineEdit("Ciao");

     Titlelayout -> addWidget(backButton);
     Titlelayout -> addStretch();
     Titlelayout -> addWidget(title);
     Titlelayout -> addStretch();
     layout -> addLayout(Titlelayout);
     layout -> addStretch();
     layout -> addWidget(text);
     layout -> addWidget(DeckName);
     layout -> addWidget(createButton);
     layout -> addStretch();


     connect(backButton,&QPushButton::clicked, this ,&NewDeckPage::BackHomePageSlot);

     connect(createButton,&QPushButton::clicked, this ,&NewDeckPage::HomeDeckPageSlot);






}

void NewDeckPage::BackHomePageSlot() {
    emit BackHomePageSignal();
}

void NewDeckPage::HomeDeckPageSlot() {
    QString NomeDeck = DeckName->text();
    if(Deck::verifyInput(NomeDeck.toStdString())){
        QLabel * Errore = new QLabel ("Sono Presenti Caratteri non riconosciuti");
        layout -> addWidget(Errore);
    }
    else {
        emit HomeDeckPageSignal();
        emit newDeckCreatedSignal(NomeDeck);
}

}

