
#include "cardinfopage.h"
#include <QGroupBox>


CardInfoPage::CardInfoPage(QWidget * parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    QVBoxLayout * headLayout = new QVBoxLayout();
    QHBoxLayout * headWidgetLayout = new QHBoxLayout();

    QHBoxLayout * imageLayout = new QHBoxLayout();
    QHBoxLayout * footerLayout = new QHBoxLayout();

    QGroupBox *cardMenu = new QGroupBox();
    cardLayout = new QHBoxLayout(cardMenu);
    image = new QLabel();
    rightImage = new ClickableLabel();
    leftImage = new ClickableLabel();
    title = new QLabel();
    title->setObjectName("Title");


    QPushButton * backButton = new QPushButton("Back");
    deleteCard = new QPushButton("Delete");
    exportPNG = new QPushButton("Export PNG");
    modifyCard = new QPushButton("Modify");

    headWidgetLayout->addWidget(backButton);
    headWidgetLayout->addSpacing(20);
    headWidgetLayout->addWidget(title, 0, Qt::AlignRight);
    headLayout->addLayout(headWidgetLayout);
    headLayout->addStretch();

    cardLayout -> addWidget(image);
    cardLayout -> setContentsMargins(0,0,0,0);

    imageLayout->addStretch();
    imageLayout->addWidget(leftImage);
    imageLayout->addSpacing(25);
    imageLayout->addWidget(cardMenu);
    imageLayout->addSpacing(25);
    imageLayout->addWidget(rightImage);
    imageLayout->addStretch();

    headLayout->addLayout(imageLayout);
    headLayout->addStretch();
    image->setAlignment(Qt::AlignCenter);

    footerLayout->addStretch();
    footerLayout->addWidget(deleteCard);

    footerLayout->addWidget(modifyCard);
    footerLayout->addWidget(exportPNG);
    footerLayout->addStretch();
    headLayout->addLayout(footerLayout);

    connect(backButton, &QPushButton::clicked, this, &CardInfoPage::BackShowDeckPageSlot);
    connect(deleteCard, &QPushButton::clicked, this, &CardInfoPage::deleteCardSlot);


    layout->addLayout(headLayout);

    backButton -> setFixedSize(155, 75);
    deleteCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    exportPNG->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    modifyCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    deleteCard->setFixedSize(200, 60);
    exportPNG->setFixedSize(200, 60);
    modifyCard->setFixedSize(200, 60);
    cardMenu ->setFixedSize(390,625);

    connect(exportPNG, &QPushButton::clicked, this, &CardInfoPage::ExportPNGSlot);
    connect(rightImage, &ClickableLabel::clicked, this, &CardInfoPage::nextImageSlot);
    connect(leftImage, &ClickableLabel::clicked, this, &CardInfoPage::previousImageSlot);
    connect(modifyCard, &QPushButton::clicked, this, &CardInfoPage::modifyCardSlot);
}


void CardInfoPage::setPixmapp(QPixmap* pixmap, Card* card) {
    QPixmap *tmp = new QPixmap(QString::fromStdString(card->getUrl()));
    image->setPixmap(*tmp);
    cardSelected = card;
}

void CardInfoPage::BackShowDeckPageSlot() {
    currentIndex = 0;
    deck = nullptr;
    cardSelected = nullptr;
    emit refreshDeckSignal();
    emit BackShowDeckPageSignal();
}
void CardInfoPage::ExportPNGSlot(){
    clearFocus();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva immagine"), "", tr("Immagini (*.png *.jpg *.bmp)"));
    if(!fileName.isEmpty()){
                QPixmap *pixmap = new QPixmap(QString::fromStdString(cardSelected->getUrl())) ;
                pixmap -> save(fileName);
     }
}

void CardInfoPage::currentDeckSlot(Deck* currDeck) {
    deck = currDeck;
    QString name = QString::fromStdString(deck->getName());
    title->setText(name);
    title->setAlignment(Qt::AlignRight);

    updateImage(cardSelected);
}


void CardInfoPage::updateImage(Card* curr) {
    // Se il mazzo contiene carte, mostra i bottoni di eliminazione ed esportazione PNG
    deleteCard->show();
    exportPNG->show();

    if (curr) {
        cardSelected = curr;
        QSize size(296, 480);

        // Imposta l'immagine corrente nella label centrale
        QString imagePath = QString::fromStdString(cardSelected->getUrl());
        QPixmap newPixmap(imagePath);

        if (newPixmap.isNull()) {
            // Se il pixmap è nullo, pulisci l'immagine visualizzata sulla QLabel image
            image->clear();
        } else {
            image->setPixmap(newPixmap.scaled(370, 600, Qt::KeepAspectRatio));

            if (deck->next(cardSelected)) {
                // Imposta l'immagine successiva nella label destra
                QString nextImagePath = QString::fromStdString(deck->next(cardSelected)->getUrl());
                QPixmap nextPixmap(nextImagePath);
                rightImage->setPixmap(nextPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }

            if (deck->prec(cardSelected)) {
                // Imposta l'immagine precedente nella label sinistra
                QString prevImagePath = QString::fromStdString(deck->prec(cardSelected)->getUrl());
                QPixmap prevPixmap(prevImagePath);
                leftImage->setPixmap(prevPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }
}




void CardInfoPage::nextImageSlot() {
    updateImage(deck->next(cardSelected));
}

void CardInfoPage::previousImageSlot() {
    updateImage(deck->prec(cardSelected));
}

void CardInfoPage::receiveImagePaths(QStringList& imagePaths) {
    this->paths = imagePaths;
}

void CardInfoPage::deleteCardSlot() {
    if (deck && cardSelected) {
        Card* nextCard = deck->next(cardSelected);

        deck->removeElement(cardSelected);
        //deck->save();

        cardSelected = nullptr;

        // Se il mazzo non è vuoto, aggiorna l'immagine con la carta successiva
        if (nextCard) {
            updateImage(nextCard);
            cardSelected = nextCard;
        } else {
            // Se il mazzo è vuoto, pulisci le immagini e il titolo
            //image->clear();
            rightImage->clear();
            leftImage->clear();
        }

        if(deck->size() == 0){

            rightImage->clear();
            leftImage->clear();

            emit BackShowDeckPageSignal();
            emit LastCardEliminatedSignal();

        }

    }

}

void CardInfoPage::modifyCardSlot(){
    emit modifyCardSignal(cardSelected);

}

void CardInfoPage::saveDeckAfterModifySlot(){
    deck->save();
}

void CardInfoPage::refreshImageSlot(Card* modified){
    updateImage(modified);
}
