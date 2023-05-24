#include "homedeckpage.h"
#include <QLabel>
#include <QDir>

HomeDeckPage::HomeDeckPage(QWidget * parent) : QWidget(parent)
{
    layout  = new QHBoxLayout(this);
    ButtonMenu = new QGroupBox();
    LastCard = new QGroupBox();
    centerImage = new QVBoxLayout();
    QVBoxLayout *col = new QVBoxLayout();
    QVBoxLayout * BoxVertical = new QVBoxLayout(ButtonMenu);
    lastCardLayout = new QVBoxLayout(LastCard);
    QHBoxLayout * Exit = new QHBoxLayout();

    header = new QLabel();
    header-> setAlignment(Qt::AlignCenter);
    header -> setObjectName("Title");
    imageLabel = new QLabel();
    stillNoCard = new QLabel();
    sadFace = new QLabel();
    QPushButton * ExitButton = new QPushButton("Log Out");
    QPushButton * DeleteButton = new QPushButton("");
    DeleteButton -> setToolTip("Delete Mazzo");
    QPushButton * ShowDeck = new QPushButton("Show Deck");
    QPushButton * GenerateCard = new QPushButton("Generate Card");
    ExitButton ->setObjectName("ExitButton");
    ShowDeck -> setObjectName("funButton");
    GenerateCard -> setObjectName("funButton");
    ButtonMenu ->setObjectName("ButtonGroupHomeDeck");
    DeleteButton ->setObjectName("DeleteButton");
    QIcon p1("asset/Icon/delete.png");
    QSize size(24, 24);



    DeleteButton->setIconSize(size);
    DeleteButton ->setIcon(p1);



    Exit -> addWidget(ExitButton);
    Exit -> addWidget(DeleteButton);
    Exit -> setAlignment(Qt::AlignCenter);
    LastCard -> setAlignment(Qt::AlignCenter);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(ShowDeck);
    BoxVertical -> addStretch();
    BoxVertical -> addWidget(GenerateCard);
    BoxVertical -> addStretch();
    BoxVertical -> addLayout(Exit);
    BoxVertical -> addSpacing(20);
    BoxVertical -> setAlignment(Qt::AlignCenter);


    ButtonMenu -> setLayout(BoxVertical);


    col->addWidget(header);
    col->addStretch();
    col->addWidget(LastCard);
    col->addStretch();
    col ->setAlignment(Qt::AlignCenter);

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

    connect(ExitButton,&QPushButton::clicked, this ,&HomeDeckPage::BackHomePageSlot);
    connect(DeleteButton,&QPushButton::clicked, this ,&HomeDeckPage::DeleteDeckSlot);
    connect(GenerateCard,&QPushButton::clicked,this , &HomeDeckPage::GenerateCardSlot);
    connect(ShowDeck, &QPushButton::clicked, this, &HomeDeckPage::ShowDeckSlot);

    sadFace -> setObjectName("Title");
    stillNoCard -> setObjectName("GHeader");
    sadFace ->setText("˙◠˙" );
    stillNoCard ->setText("The Deck is Empty");
    sadFace ->setAlignment(Qt::AlignCenter);
    stillNoCard ->setAlignment(Qt::AlignCenter);
    lastCardLayout ->setAlignment(Qt::AlignCenter);
    centerImage -> setAlignment(Qt::AlignCenter);

    centerImage ->addWidget(imageLabel);
    centerImage ->addWidget(sadFace);
    centerImage ->addWidget(stillNoCard);
    lastCardLayout ->addLayout(centerImage);


    lastCardLayout -> setContentsMargins(0,0,0,0);
    centerImage-> setContentsMargins(0,0,0,0);

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


    // Visualizzazione della finestra di dialogo e recupero della risposta
    int ret = msgBox.exec();

    // Gestione della risposta
    if (ret == QMessageBox::Yes) {
    deck.clear(); //pulisco il mazzo da quello precedente
    emit BackHomePageSignal();
    }

}

void HomeDeckPage::DeleteDeckSlot() {
    QMessageBox msgBox;
    msgBox.setText("Rimozione Mazzo");
    msgBox.setInformativeText("Tutte le carte e tutte le immagini di esso verrano cancellate. \nSei Sicuro?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    // Visualizzazione della finestra di dialogo e recupero della risposta
    int ret = msgBox.exec();

    // Gestione della risposta
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
    //emit ClearShowDeckPageSignal();

}

