#include "homepage.h"
#include <iostream>

HomePage::HomePage(QWidget * parent) : QWidget(parent)
{
    mode=1;
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *Button1 = new QHBoxLayout();
    QHBoxLayout *Button2 = new QHBoxLayout();
    QHBoxLayout *Button3 = new QHBoxLayout();
    QHBoxLayout *footer = new QHBoxLayout();

    QPushButton *Manualbutton = new QPushButton("Read Manual");
    QPushButton *NewDeckButton = new QPushButton("Create New Deck");
    QPushButton *LoadDeckButton = new QPushButton("Load Existing Deck");
    theme = new QPushButton();
    QLabel *title = new QLabel("Welcome To ArcaneOracle");
    title-> setObjectName("HomePageTitle");

    QPixmap p1("asset/Icon/LightM.png");

    QSize size(24, 24);
    p1 = p1.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    theme->setIconSize(size);
    theme ->setIcon(p1);

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
    layout -> addLayout(footer);

    footer -> addStretch();
    footer -> addWidget(theme);

    layout->setAlignment(Qt::AlignCenter);
    title->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);

    NewDeckButton -> setFixedSize(330, 80);
    LoadDeckButton -> setFixedSize(330, 80);
    Manualbutton -> setFixedSize(330, 80);
    theme -> setFixedSize(50, 50);

    connect(Manualbutton,&QPushButton::clicked, this,&HomePage::ManualHomePageSlot);
    connect(NewDeckButton,&QPushButton::clicked, this,&HomePage::NewDeckPageSlot);
    connect(LoadDeckButton,&QPushButton::clicked, this, &HomePage::LoadDeckPageSlot);
    connect(theme,&QPushButton::clicked, this, &HomePage::lightmodeSlot);

}

void HomePage::lightmodeSlot() {
    mode=((mode+1)%2);
    std::string path ;
    switch (mode) {
    case 0:
        path ="asset/Icon/DarkM.png";
        break;
    case 1:
        path ="asset/Icon/LightM.png";
        break;
    default:
        break;

    }
    QPixmap p7(path.c_str());
    QSize size(24, 24);
    p7 = p7.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    theme->setIcon(p7);
    theme->setIconSize(size);
    emit lightmodeSignal(mode);
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
