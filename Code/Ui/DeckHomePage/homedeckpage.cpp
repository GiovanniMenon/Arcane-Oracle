#include "homedeckpage.h"


HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QHBoxLayout(this);
    ButtonMenu = new QGroupBox();
    LastCard = new QGroupBox();
    centerImage = new QVBoxLayout();

    QVBoxLayout *col = new QVBoxLayout();
    QVBoxLayout * BoxVertical = new QVBoxLayout(ButtonMenu);
    QHBoxLayout * Exit = new QHBoxLayout();


    lastCardLayout = new QVBoxLayout(LastCard);
    header = new QLabel();

    imageLabel = new QLabel();
    stillNoCard = new QLabel();
    sadFace = new QLabel();

    QPushButton * ExitButton = new QPushButton("Log Out");
    QPushButton * DeleteButton = new QPushButton("");
    QPushButton * ShowDeck = new QPushButton("Show Deck");
    QPushButton * GenerateCard = new QPushButton("Generate Card");

    ExitButton ->setObjectName("ExitButton");
    ShowDeck -> setObjectName("funButton");
    GenerateCard -> setObjectName("funButton");
    ButtonMenu ->setObjectName("ButtonGroupHomeDeck");
    DeleteButton ->setObjectName("DeleteButton");
    DeleteButton -> setToolTip("Delete Mazzo");
    DeleteButton->setStyleSheet("QToolTip { color: #1c1c1c; }");
    header -> setObjectName("Title");

    QIcon p1("asset/Icon/delete.png");
    QSize size(24, 24);



    DeleteButton->setIconSize(size);
    DeleteButton ->setIcon(p1);



    Exit -> addWidget(ExitButton);
    Exit -> addWidget(DeleteButton);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(ShowDeck);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(GenerateCard);
    BoxVertical -> addStretch();
    BoxVertical -> addLayout(Exit);
    BoxVertical -> addSpacing(20);



    ButtonMenu -> setLayout(BoxVertical);


    col->addWidget(header);
    col->addStretch();
    col->addWidget(LastCard);
    col->addStretch();


    layout -> addSpacing(50);
    layout -> addWidget(ButtonMenu);
    layout -> addStretch();
    layout -> addLayout(col);
    layout -> addSpacing(50);


    ExitButton -> setFixedSize(155, 60);
    ShowDeck -> setFixedSize(260, 80);
    GenerateCard-> setFixedSize(260, 80);
    ButtonMenu -> setFixedSize(400, 750);
    LastCard -> setFixedSize(390, 625);
    DeleteButton -> setFixedSize(60, 60);



    sadFace -> setObjectName("Title");
    stillNoCard -> setObjectName("GHeader");
    sadFace -> setText("˙◠˙" );
    stillNoCard ->setText("The Deck is Empty");


    sadFace ->setAlignment(Qt::AlignCenter);
    stillNoCard ->setAlignment(Qt::AlignCenter);
    lastCardLayout ->setAlignment(Qt::AlignCenter);
    centerImage -> setAlignment(Qt::AlignCenter);
    col ->setAlignment(Qt::AlignCenter);
    Exit -> setAlignment(Qt::AlignCenter);
    LastCard -> setAlignment(Qt::AlignCenter);
    header-> setAlignment(Qt::AlignCenter);
    BoxVertical -> setAlignment(Qt::AlignCenter);

    centerImage ->addWidget(imageLabel);
    centerImage ->addWidget(sadFace);
    centerImage ->addWidget(stillNoCard);

    lastCardLayout ->addLayout(centerImage);


    lastCardLayout -> setContentsMargins(0,0,0,0);
    centerImage-> setContentsMargins(0,0,0,0);

    connect(ExitButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
    connect(DeleteButton,&QPushButton::clicked, this ,&HomeDeckPage::DeleteDeckSlot);
    connect(GenerateCard,&QPushButton::clicked,this , &HomeDeckPage::GenerateCardSlot);
    connect(ShowDeck, &QPushButton::clicked, this, &HomeDeckPage::ShowDeckSlot);

}
void HomeDeckPage::lastCardGenerate() const {
    if(!deck.is_empty()){
            imageLabel -> show();
            stillNoCard -> hide();
            sadFace -> hide();
            QPixmap lastCard = (QString::fromStdString(deck.last()->getUrl()));
            imageLabel ->setPixmap(lastCard);
    }else{
            imageLabel -> hide();
            sadFace -> show();
            stillNoCard -> show();

    }

}

void HomeDeckPage::GenerateCardSlot() {
    emit DeckSelectedSignal(&deck);
    emit GenerateCardSignal();

}

void HomeDeckPage::BackHomePageSlot() {
    QMessageBox msgBox;
    msgBox.setText("Log Out");
    msgBox.setInformativeText("Tutte le modifiche non salvate verrano perse. \nSei Sicuro di voler uscire?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
    deck.clear();
    emit BackHomePageSignal();
    }

}

void HomeDeckPage::DeleteDeckSlot() {
    QMessageBox msgBox;
    msgBox.setText("Rimozione Mazzo");
    msgBox.setInformativeText("Tutte le carte e tutte le immagini di esso verrano cancellate. \nSei Sicuro?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
    deck.clear();
    std::string deckNamePath =deck.getName();
    deckNamePath.erase(std::remove_if(deckNamePath.begin(), deckNamePath.end(), ::isspace),
    deckNamePath.end());

    std::string deckPath = "asset/Deck/" + deckNamePath ;
    QDir directory(QString::fromStdString(deckPath));
    directory.removeRecursively();
    emit BackHomePageSignal();
    }

}

void HomeDeckPage::newDeckCreatedSlot(QString nomeDeck) {

    deck.SetDeck(nomeDeck.toStdString());
    header -> setText(QString::fromStdString(deck.getName()));

    lastCardGenerate();
}

void HomeDeckPage::ShowDeckSlot() {
    emit ShowDeckSignal();
    emit DeckSelectedSignal(&deck);
}

