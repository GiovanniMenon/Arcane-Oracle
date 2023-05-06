#include "loadpage.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <dirent.h>
#include <QDir>
#include <QFileInfo>
#include <QRadioButton>



LoadPage::LoadPage(QWidget *parent) : QWidget(parent)
{
    layout  = new QVBoxLayout(this);

    QHBoxLayout * Back  = new QHBoxLayout();
    QHBoxLayout * Title  = new QHBoxLayout();

    QHBoxLayout * LoadLayout  = new QHBoxLayout();


    QPushButton *backButton = new QPushButton("Back");
    QPushButton *loadButton = new QPushButton("Load");
    QLabel *title = new QLabel("Choose your Deck");
    title -> setObjectName("Title");




    Back -> addWidget(backButton);
    Back -> addStretch();

    Title -> addWidget(title);
    Title -> setAlignment(Qt::AlignCenter);

    layout -> addLayout(Back);
    layout -> addLayout(Title);
    layout -> addStretch();





    if(opendir("asset")){


         layout -> addWidget(loadDeckGroup());

    }else{
         QLabel *notFound = new QLabel("Nessun Mazzo Presente");
         layout -> addWidget(notFound);
    }

    layout -> addStretch();
    layout->  setAlignment(Qt::AlignCenter);
    LoadLayout -> addStretch();
    LoadLayout -> addWidget(loadButton);
    LoadLayout -> addStretch();
    layout -> addLayout(LoadLayout);
    layout -> addStretch();

    backButton -> setFixedSize(150, 60);
    loadButton -> setFixedSize(250, 70);
    groupBox -> setFixedHeight(400);



    connect(backButton,&QPushButton::clicked, this ,&LoadPage::BackHomePageSlot);
    connect(loadButton,&QPushButton::clicked, this ,&LoadPage::HomeDeckPageSlot);

}
void LoadPage::HomeDeckPageSlot() {
    if(buttonGroup->checkedButton()!=nullptr){
    QString CheckedButton = QString::number(buttonGroup -> checkedId());
    emit HomeDeckPageSignal();
    emit newDeckCreatedSignal(QString::fromStdString(NomiDeck[CheckedButton.toInt()]));
    }
}
void LoadPage::BackHomePageSlot(){
    emit BackHomePageSignal();
}

QGroupBox *LoadPage::loadDeckGroup(){
    groupBox = new QGroupBox(tr("Deck List: "));
    buttonGroup = new QButtonGroup(this);
    vbox = new QVBoxLayout(groupBox);
    SearchDeck();
    return groupBox;
}

void LoadPage::refresh(){
    for(QAbstractButton *button : buttonGroup->buttons()) {
        buttonGroup->removeButton(button);
        delete button;
    }
    SearchDeck();
}

void LoadPage::SearchDeck(){
    QString path = "asset/Deck/";
    QDir directory(path);
    directory.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);


    NomiDeck.clear();
    QFileInfoList fileList = directory.entryInfoList();

    int i = 0;
    foreach(QFileInfo directory, fileList) {
        QString Deck_name = directory.fileName();
        NomiDeck.push_back(Deck_name.toStdString());

        QRadioButton *checkButton = new QRadioButton(Deck_name);
        buttonGroup->addButton(checkButton, i);

        vbox->addWidget(checkButton);
        i++;
    }
    vbox ->  setAlignment(Qt::AlignTop);

}
