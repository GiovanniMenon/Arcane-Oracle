#include "homepage.h"
#include <iostream>

HomePage::HomePage(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *Manualbutton = new QPushButton("Read Manual");
    QPushButton *NewDeckButton = new QPushButton("New Deck");
    QPushButton *LoadDeckButton = new QPushButton("Load Deck");
    QLabel *title = new QLabel("ArcaneOracle");


    layout -> addWidget(title);
    layout -> addStretch();
    layout -> addWidget(NewDeckButton);
    layout -> addWidget(LoadDeckButton);
    layout -> addWidget(Manualbutton);
    layout -> addStretch();
    layout->setAlignment(Qt::AlignCenter);


    connect(Manualbutton,&QPushButton::clicked, this,&HomePage::ManualHomePageSlot);
    connect(NewDeckButton,&QPushButton::clicked, this,&HomePage::NewDeckPageSlot);
    connect(LoadDeckButton,&QPushButton::clicked, this, &HomePage::LoadDeckPageSlot);
}

void HomePage::ManualHomePageSlot() {
    emit ManualHomePageSignal();
}

void HomePage::NewDeckPageSlot() {
    emit NewDeckPageSignal();
}

void HomePage::LoadDeckPageSlot() {
    emit LoadDeckPageSignal();
}
