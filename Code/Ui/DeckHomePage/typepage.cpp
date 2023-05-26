#include "typepage.h"


#include <QEvent>


#include "../Visitor/monsterwidget.h"
#include "../Visitor/trapwidget.h"
#include "../Visitor/artifactwidget.h"
#include "../Visitor/fieldwidget.h"
#include "../Visitor/spellwidget.h"




TypePage::TypePage(QWidget * parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    ButtonMenu = new QGroupBox();
    QHBoxLayout * Head = new QHBoxLayout();
    QHBoxLayout * Title = new QHBoxLayout();
    QHBoxLayout * Choice = new QHBoxLayout(ButtonMenu);
    QHBoxLayout * Desc = new QHBoxLayout();
    QHBoxLayout * Footer = new QHBoxLayout();

    QPushButton * backButton = new QPushButton("EXIT");
    QLabel * TextTitle = new QLabel("Choose your Card Type");
    DescText = new QLabel();



    QPushButton * Monster = new QPushButton("Monster");
    QPushButton * Field = new QPushButton("Field");
    QPushButton * Artifact = new QPushButton("Artifact");
    QPushButton * Spell = new QPushButton("Spell");
    QPushButton * Trap = new QPushButton("Trap");

    Descrizioni.push_back("La Carta Mostro rappresenta una Creatura, e' dotata di diversi Campi Unici.\n Ogni Carta Mostro ha un LIVELLO, una DIFESA ,un ATTACCO e dei PUNTI . \nAlcuni esempi possono essere: Un tipo di Drago");
    Descrizioni.push_back("La Carta Terreno rappresenta un Ambiente Naturale o un Zona .\n Ogni Carta terreno e' composta dall'elemento (ACQUA , FUOCO , ARIA , TERRA) e dall'effetto che applica. \n Alcuni Esempi possono essere: Una Foresta, Un Deserto, Un Oceano ...");
    Descrizioni.push_back("Le carte Artefatto rappresentano degli equipaggiamenti per le Carte Mostro. \n Si divino in ARMATURE , POZIONI e ARMI. \n Hanno degli atributi unici come DIFESA e ATTACCO.");
    Descrizioni.push_back("Le carte Maga rappresentano diversi tipi di Incantesimi. \n Si divino in varie Categorie in base al Tipo. \n Ogni magia ha un DANNO e un EFFETTO.");
    Descrizioni.push_back("Le carte Trappola rappresentano diversi tipi di Trappole e Maledizioni. \n Hanno diversi campi Unici tra cui la DURATA della maledizione e il DANNO di essa. \n Inoltre ogni carta Trappola e' dotata di un EFFETTO");


    backButton -> setFixedSize(155, 60);


    Monster -> setFixedSize(200, 85);
    Field -> setFixedSize(200, 85);
    Artifact -> setFixedSize(200, 85);
    Spell -> setFixedSize(200, 85);
    Trap -> setFixedSize(200, 85);
    ButtonMenu -> setFixedHeight(200);

    TextTitle -> setObjectName("Title");
    ButtonMenu -> setObjectName("TypeMenu");
    Spell ->setObjectName("cardType1");
    Trap -> setObjectName("cardType2");
    Monster -> setObjectName("cardType3");
    Field ->  setObjectName("cardType4");
    Artifact -> setObjectName("cardType5");



    Spell->setProperty("id", "3");
    Trap->setProperty("id", "4");
    Monster->setProperty("id", "0");
    Field->setProperty("id", "1");
    Artifact->setProperty("id", "2");



    Head -> addWidget(backButton);
    Head -> addStretch();

    Title -> addWidget(TextTitle);
    Title -> setAlignment(Qt::AlignCenter);

    DescText ->setAlignment(Qt::AlignCenter);
    Desc -> addWidget(DescText);
    Desc -> setAlignment(Qt::AlignCenter);

    Choice -> addWidget(Monster);
    Choice -> addWidget(Field);
    Choice -> addWidget(Artifact);
    Choice -> addWidget(Spell);
    Choice -> addWidget(Trap);
    ButtonMenu -> setLayout(Choice);

    Footer -> addStretch();

    layout -> addLayout(Head);
    layout -> addStretch();
    layout -> addLayout(Title);
    layout -> addStretch();
    layout -> addWidget(ButtonMenu);
    layout -> addStretch();
    layout -> addLayout(Desc);
    layout -> addStretch();
    layout -> addLayout(Footer);

    connect(backButton,&QPushButton::clicked, this ,&TypePage::BackDeckPageSlot);


    Monster->installEventFilter(this);
    Field->installEventFilter(this);
    Artifact->installEventFilter(this);
    Spell->installEventFilter(this);
    Trap->installEventFilter(this);


    connect(Monster,&QPushButton::clicked, this ,&TypePage::CardSlot);
    connect(Field,&QPushButton::clicked, this ,&TypePage::CardSlot);
    connect(Artifact,&QPushButton::clicked, this ,&TypePage::CardSlot);
    connect(Spell,&QPushButton::clicked, this ,&TypePage::CardSlot);
    connect(Trap,&QPushButton::clicked, this ,&TypePage::CardSlot);

}


bool TypePage::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Enter) {
                QPushButton* button = qobject_cast<QPushButton*>(obj);
                DescText -> setText(Descrizioni[button->property("id").toInt()]);
    }

    return 0;
}

void TypePage::BackDeckPageSlot() {
    emit BackDeckPageSignal();
}

void TypePage::CardSlot() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    emit CreateCardPageSignal();
    emit CardSignal(deck , cardWidgets[clickedButton->property("id").toInt()]);

}

void TypePage::currentDeckSlot(Deck * currDeck){
    deck = currDeck;

    cardWidgets.clear();

    cardWidgets.push_back(new monsterWidget(deck));
    cardWidgets.push_back(new fieldWidget(deck));
    cardWidgets.push_back(new artifactWidget(deck));
    cardWidgets.push_back(new spellWidget(deck));
    cardWidgets.push_back(new trapWidget(deck));




}
