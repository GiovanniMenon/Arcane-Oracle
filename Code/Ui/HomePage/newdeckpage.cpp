#include "newdeckpage.h"
#include <QPushButton>
#include <QLabel>

#include <iostream>
NewDeckPage::NewDeckPage(QWidget *parent) :  QWidget(parent)
{
     QVBoxLayout * layout  = new QVBoxLayout(this);



     QPushButton *backButton = new QPushButton("Back");
     QPushButton *createButton = new QPushButton("Create");
     QLabel *title = new QLabel("Create your Own Deck");
     QLabel *text = new QLabel("Enter the name of your deck");
     QLineEdit *DeckName = new QLineEdit("Ciao");

     backButton -> setMaximumWidth(200);
     createButton -> setMaximumWidth(200);
     DeckName -> setMaximumWidth(300);

     layout -> addWidget(backButton);
     layout -> addWidget(title);
     layout -> addStretch();
     layout -> addWidget(text);
     layout -> addWidget(DeckName);
     layout -> addWidget(createButton);
     layout -> addStretch();
     layout->  setAlignment(Qt::AlignCenter);

     connect(backButton,&QPushButton::clicked, this ,&NewDeckPage::BackHomePageSlot);
     connect(createButton,&QPushButton::clicked, this ,&NewDeckPage::HomeDeckPageSlot);



}

void NewDeckPage::BackHomePageSlot() {
    emit BackHomePageSignal();
}

void NewDeckPage::HomeDeckPageSlot() {
    emit HomeDeckPageSignal();
}
