#include "homepage.h"
#include <iostream>

HomePage::HomePage(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *Button1 = new QHBoxLayout();
    QHBoxLayout *Button2 = new QHBoxLayout();
    QHBoxLayout *Button3 = new QHBoxLayout();

    QPushButton *Manualbutton = new QPushButton("Read Manual");
    QPushButton *NewDeckButton = new QPushButton("Create New Deck");
    QPushButton *LoadDeckButton = new QPushButton("Load Existing Deck");
    QLabel *title = new QLabel("Welcome To ArcaneOracle");
    title-> setObjectName("HomePageTitle");

    Button1 -> addWidget(NewDeckButton);
    Button1 ->setAlignment(Qt::AlignCenter);
    Button2 -> addWidget(LoadDeckButton);
    Button2 ->setAlignment(Qt::AlignCenter);
    Button3-> addWidget(Manualbutton);
    Button3 ->setAlignment(Qt::AlignCenter);



    layout -> addWidget(title);
    layout -> addStretch();
    layout -> addLayout(Button1);
     layout -> addSpacing(15);
    layout -> addLayout(Button2);
    layout -> addSpacing(15);
    layout -> addLayout(Button3);
    layout -> addStretch();
    layout->setAlignment(Qt::AlignCenter);
    title->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    NewDeckButton -> setFixedSize(330, 80);
    LoadDeckButton -> setFixedSize(330, 80);
    Manualbutton -> setFixedSize(330, 80);





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
