#include "cardpage.h"

#include <QHoverEvent>
#include <QEvent>
#include <QDebug>

CardPage::CardPage(QWidget * parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    QHBoxLayout * Head = new QHBoxLayout();
    QHBoxLayout * Title = new QHBoxLayout();
    QHBoxLayout * Choice = new QHBoxLayout();
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

    Spell ->setStyleSheet("QPushButton { border: 2px solid #b9d7d9; border-radius: 15px; } QPushButton:hover { background-color: #b9d7d9; color: black; }");
    Trap -> setStyleSheet("QPushButton { border: 2px solid #9370db; border-radius: 15px; } QPushButton:hover { background-color: #9370db; color: white; }");
    Monster -> setStyleSheet("QPushButton { border: 2px solid #a66e4a; border-radius: 15px; } QPushButton:hover { background-color: #a66e4a; color: white; }");
    Field -> setStyleSheet("QPushButton { border: 2px solid #87a96b; border-radius: 15px; } QPushButton:hover { background-color: #87a96b; color: white; }");
    Artifact -> setStyleSheet("QPushButton { border: 2px solid #f2af6d; border-radius: 15px; } QPushButton:hover { background-color: #f2af6d; color: white; }");

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

    Footer -> addStretch();
    //Footer -> addWidget(Submit);


    layout -> addLayout(Head);
    layout -> addStretch();
    layout -> addLayout(Title);
    layout -> addStretch();
    layout -> addLayout(Choice);
    layout -> addStretch();
    layout -> addLayout(Desc);
    layout -> addStretch();
    layout -> addLayout(Footer);

    connect(backButton,&QPushButton::clicked, this ,&CardPage::BackDeckPageSlot);


    Monster->installEventFilter(this);
    Field->installEventFilter(this);
    Artifact->installEventFilter(this);
    Spell->installEventFilter(this);
    Trap->installEventFilter(this);

}


bool CardPage::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::Enter) {
                QPushButton* button = qobject_cast<QPushButton*>(obj);
                DescText -> setText(Descrizioni[button->property("id").toInt()]);
    }

    return 0;
}

void CardPage::BackDeckPageSlot() {
    emit BackDeckPageSignal();
}
