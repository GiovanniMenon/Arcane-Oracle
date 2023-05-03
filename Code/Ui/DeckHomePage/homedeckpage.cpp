#include "homedeckpage.h"

HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * layout  = new QVBoxLayout(this);
    QPushButton *backButton = new QPushButton("EXIT");
    layout -> addWidget(backButton);
    connect(backButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
}

void HomeDeckPage::BackHomePageSlot() {
    emit BackHomePageSignal();
}

