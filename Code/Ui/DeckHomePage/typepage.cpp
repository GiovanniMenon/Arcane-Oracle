#include "typepage.h"

#include <QHoverEvent>
#include <QEvent>
#include <QDebug>

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
    DescText = new QLabel("");


    QPushButton * Submit = new QPushButton("Avanti");
    QPushButton * Monster = new QPushButton("Monster");
    QPushButton * Field = new QPushButton("Field");
    QPushButton * Artifact = new QPushButton("Artifact");
    QPushButton * Spell = new QPushButton("Spell");
    QPushButton * Trap = new QPushButton("Trap");

    Descrizioni.push_back("Descrizione Mostro");
    Descrizioni.push_back("Descrizione Field");
    Descrizioni.push_back("Descrizione Artifact");
    Descrizioni.push_back("Descrizione Spell");
    Descrizioni.push_back("Descrizione Trap");


    backButton -> setFixedSize(155, 60);
    Submit -> setFixedSize(170, 80);

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

    Desc -> addWidget(DescText);
    Desc -> setAlignment(Qt::AlignCenter);

    Choice -> addWidget(Monster);
    Choice -> addWidget(Field);
    Choice -> addWidget(Artifact);
    Choice -> addWidget(Spell);
    Choice -> addWidget(Trap);
    ButtonMenu -> setLayout(Choice);

    Footer -> addStretch();
    //Footer -> addWidget(Submit);


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
    emit CardSignal(clickedButton->property("id").toInt());
}
