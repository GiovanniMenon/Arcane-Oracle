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


using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;


LoadPage::LoadPage(QWidget *parent) : QWidget(parent)
{
    layout  = new QVBoxLayout(this);

    QHBoxLayout * TitleLayout  = new QHBoxLayout();
    QHBoxLayout * LoadLayout  = new QHBoxLayout();


    QPushButton *backButton = new QPushButton("Back");
    QPushButton *loadButton = new QPushButton("Load");
    QLabel *title = new QLabel("Load your  Deck");


    loadButton->setStyleSheet("font: bold;background-color: red;font-size: 36px;height: 48px;width: 120px;");

    TitleLayout -> addWidget(backButton);
    TitleLayout -> addStretch();
    TitleLayout -> addWidget(title);
    TitleLayout -> addStretch();
    layout -> addLayout(TitleLayout);
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


    connect(backButton,&QPushButton::clicked, this ,&LoadPage::BackHomePageSlot);
    connect(loadButton,&QPushButton::clicked, this ,&LoadPage::HomeDeckPageSlot);

}
void LoadPage::HomeDeckPageSlot() {

    QString CheckedButton = QString::number(buttonGroup -> checkedId());
    emit HomeDeckPageSignal();
    emit newDeckCreatedSignal(QString::fromStdString(NomiDeck[CheckedButton.toInt()]));
}
void LoadPage::BackHomePageSlot(){
    emit BackHomePageSignal();
}

QGroupBox *LoadPage::loadDeckGroup(){
    QGroupBox *groupBox = new QGroupBox(tr("Lista Mazzi : "));
    buttonGroup = new QButtonGroup(this);
    vbox = new QVBoxLayout(groupBox);

    string path = "asset/Deck/";

    int i = 0;
    for (const auto & file : directory_iterator(path)){
          std::string name = file.path().c_str();
          name.erase(0,11);
          NomiDeck.push_back(name);
          QRadioButton *checkButton = new QRadioButton(name.c_str());
          buttonGroup -> addButton(checkButton,i);
          vbox ->addWidget(checkButton);
          i++;
       }
    groupBox -> setLayout(vbox);
    return groupBox;
}

void LoadPage::refresh(){
    for(QAbstractButton *button : buttonGroup->buttons()) {

        buttonGroup->removeButton(button);
        delete button;
    }
    string path = "asset/Deck/";
    NomiDeck.clear();
    int i = 0;
    for (const auto & file : directory_iterator(path)){
          std::string name = file.path().c_str();
          name.erase(0,11);
          NomiDeck.push_back(name);
          QRadioButton *checkButton = new QRadioButton(name.c_str());
          buttonGroup -> addButton(checkButton,i);
          vbox ->addWidget(checkButton);
          i++;
       }

}
