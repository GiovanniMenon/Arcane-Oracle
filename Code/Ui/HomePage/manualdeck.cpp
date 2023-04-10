#include "manualdeck.h"

#include <QTextEdit>
#include <QVBoxLayout>

#include <QFile>
#include <iostream>
#include <QLabel>
#include <QPushButton>

ManualDeck::ManualDeck(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * layout  = new QVBoxLayout(this);


    QFile manualText("manualDeck.txt");
    manualText.open(QFile::ReadOnly);
    std::string text = manualText.readAll().toStdString();


    QPushButton *backButton = new QPushButton("Back");
    QLabel *title = new QLabel("ArcaneOracleManual");
    QTextEdit *manual = new QTextEdit(QString::fromStdString(text));
    layout -> addWidget(backButton);
    backButton -> setMaximumWidth(200);
    layout -> addWidget(title);
    layout -> addStretch();
    layout -> addWidget(manual);
    layout -> addStretch();
    layout->  setAlignment(Qt::AlignCenter);

    connect(backButton,&QPushButton::clicked, this ,&ManualDeck::BackHomePageSlot);
}

void ManualDeck::BackHomePageSlot() {
    emit BackHomePageSignal();
}
