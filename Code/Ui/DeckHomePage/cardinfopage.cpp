#include "cardinfopage.h"


CardInfoPage::CardInfoPage(QWidget * parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    QVBoxLayout * headLayout = new QVBoxLayout();
    QHBoxLayout * headWidgetLayout = new QHBoxLayout();
    QHBoxLayout * imageLayout = new QHBoxLayout();
    QHBoxLayout * footerLayout = new QHBoxLayout();

    image = new QLabel();
    rightImage = new ClickableLabel();
    leftImage = new ClickableLabel();
    title = new QLabel();
    title->setObjectName("Title");



    QPushButton * backButton = new QPushButton("Back");
    QPushButton * deleteCard = new QPushButton("Delete");
    QPushButton * exportPNG = new QPushButton("Export PNG");

    headWidgetLayout->addWidget(backButton);
    headWidgetLayout->addSpacing(20);
    headWidgetLayout->addWidget(title, 0, Qt::AlignRight);
    headLayout->addLayout(headWidgetLayout);
    headLayout->addStretch();

    imageLayout->addWidget(leftImage);
    imageLayout->addStretch();
    imageLayout->addWidget(image);
    imageLayout->addStretch();
    imageLayout->addWidget(rightImage);

    headLayout->addLayout(imageLayout);
    headLayout->addStretch();
    image->setAlignment(Qt::AlignCenter);

    footerLayout->addStretch();
    footerLayout->addWidget(deleteCard);
    footerLayout->addWidget(exportPNG);
    footerLayout->addStretch();
    headLayout->addLayout(footerLayout);

    connect(backButton, &QPushButton::clicked, this, &CardInfoPage::BackShowDeckPageSlot);


    layout->addLayout(headLayout);

    backButton->setFixedSize(155, 60);
    deleteCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    exportPNG->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    deleteCard->setFixedSize(200, 60);
    exportPNG->setFixedSize(200, 60);

    connect(exportPNG, &QPushButton::clicked, this, &CardInfoPage::ExportPNGSlot);
    connect(rightImage, &ClickableLabel::clicked, this, &CardInfoPage::nextImageSlot);
    connect(leftImage, &ClickableLabel::clicked, this, &CardInfoPage::previousImageSlot);
}


void CardInfoPage::setPixmapp(QPixmap* pixmap, Card* card) {
    this->pixmap = pixmap;
    image->setPixmap(*pixmap);

    cardSelected = card;

}





void CardInfoPage::BackShowDeckPageSlot() {
    currentIndex = 0;
    deck = nullptr;
    cardSelected = nullptr;
    emit BackShowDeckPageSignal();
}

void CardInfoPage::ExportPNGSlot(){
    QString filePath = QFileDialog::getSaveFileName(this, "Export PNG", "", "Immagini (*.png *.xpm *.jpg)");

    if(!filePath.isEmpty()){
            QImage img = image->pixmap().toImage();
            img.save(filePath);
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
    cardSelected = curr;
    QSize size(185,300);
    // Imposta l'immagine corrente nella label centrale
    QString imagePath = QString::fromStdString(cardSelected->getUrl());
    QPixmap newPixmap(imagePath);

    image->setPixmap(newPixmap.scaled(500, 500, Qt::KeepAspectRatio));

    // Imposta l'immagine successiva nella label destra
    QString nextImagePath = QString::fromStdString(deck->next(cardSelected)->getUrl());
    QPixmap nextPixmap(nextImagePath);
    rightImage->setPixmap(nextPixmap.scaled(size, Qt::KeepAspectRatio));

    // Imposta l'immagine precedente nella label sinistra
    QString prevImagePath = QString::fromStdString(deck->prec(cardSelected)->getUrl());
    QPixmap prevPixmap(prevImagePath);
    leftImage->setPixmap(prevPixmap.scaled(size, Qt::KeepAspectRatio));
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
