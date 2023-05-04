#include "homedeckpage.h"
#include <QLabel>
#include "../HomePage/newdeckpage.h"

HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QVBoxLayout(this);
    QHBoxLayout * Title = new QHBoxLayout();
    QPushButton * backButton = new QPushButton("EXIT");
    nome1 = new QLabel();



    Title -> addWidget(backButton);
    Title -> addStretch();
    Title -> addWidget(nome1);
    Title -> addStretch();
    layout -> addLayout(Title);
    layout -> addStretch();
    connect(backButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);



}

void HomeDeckPage::BackHomePageSlot() {
    deck.clear(); //pulisco il mazzo da quello precedente
    emit BackHomePageSignal();
}
void HomeDeckPage::newDeckCreatedSlot(QString nomeDeck) {
    nome1 -> setText(nomeDeck);
    deck.SetDeck(nomeDeck.toStdString());
}

