#include "manualdeck.h"

#include <QTextEdit>
#include <QVBoxLayout>

#include <QFile>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QScrollBar>


ManualDeck::ManualDeck(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * layout  = new QVBoxLayout(this);
    QHBoxLayout * Back  = new QHBoxLayout();
    QHBoxLayout * Title  = new QHBoxLayout();


    QFile manualText("asset/Manual/manualDeck.txt");
    manualText.open(QFile::ReadOnly);
    std::string text = manualText.readAll().toStdString();


    QPushButton *backButton = new QPushButton("Back");
    QLabel *title = new QLabel("ArcaneOracle Manual");
    title -> setObjectName("Title");
    QTextEdit *manual = new QTextEdit(QString::fromStdString(text));
    Back -> addWidget(backButton);
    Back -> addStretch();

    backButton -> setFixedSize(155, 60);
    manual -> setFixedHeight(550);
    manual -> setReadOnly(true);

    Title -> addWidget(title);
    Title ->  setAlignment(Qt::AlignCenter);

    layout ->addLayout(Back);
    layout -> addLayout(Title);
    layout -> addSpacing(30);
    layout -> addWidget(manual);
    layout -> addStretch();
    layout->  setAlignment(Qt::AlignCenter);

    connect(backButton,&QPushButton::clicked, this ,&ManualDeck::BackHomePageSlot);
}

void ManualDeck::BackHomePageSlot() {
    emit BackHomePageSignal();
}
