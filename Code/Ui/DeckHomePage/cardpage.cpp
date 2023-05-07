#include "cardpage.h"
#include <QLabel>

CardPage::CardPage()
{
    main = new QVBoxLayout(this);
}


void CardPage::NewCardIdSlot(int i) {

    QLabel *id = new QLabel(QString::number(i));

    main->addWidget(id);
}

