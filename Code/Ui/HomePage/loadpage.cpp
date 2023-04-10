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
    QVBoxLayout * layout  = new QVBoxLayout(this);



    QPushButton *backButton = new QPushButton("Back");
    QPushButton *loadButton = new QPushButton("Load");
    QLabel *title = new QLabel("Load your  Deck");








    backButton -> setMaximumWidth(200);
    loadButton -> setMaximumWidth(200);


    layout -> addWidget(backButton);
    layout -> addWidget(title);
    layout -> addStretch();

    if(opendir("asset")){
         layout -> addWidget(loadDeckGroup());
    }else{
         QLabel *notFound = new QLabel("Nessun Mazzo Presente");
         layout -> addWidget(notFound);
    }

    layout -> addStretch();
    layout->  setAlignment(Qt::AlignCenter);
    layout -> addWidget(loadButton);
    layout -> addStretch();

    connect(backButton,&QPushButton::clicked, this ,&LoadPage::BackHomePageSlot);
}

void LoadPage::BackHomePageSlot(){
    emit BackHomePageSignal();
}

QGroupBox *LoadPage::loadDeckGroup(){
    QGroupBox *groupBox = new QGroupBox(tr("Lista Mazzi : "));
    string path = "asset/";
    QVBoxLayout *vbox = new QVBoxLayout;
    for (const auto & file : directory_iterator(path)){
          std::string name = file.path().c_str();
          QRadioButton *checkButton = new QRadioButton(name.c_str());
          vbox -> addWidget(checkButton);
       }

    groupBox -> setLayout(vbox);
    return groupBox;


}
