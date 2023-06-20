#include "cardinfopage.h"


CardInfoPage::CardInfoPage(QWidget * parent) : QWidget(parent) {

    QVBoxLayout * headLayout = new QVBoxLayout(this);

    QVBoxLayout * nextLayout = new QVBoxLayout();
    QVBoxLayout * cardLayoutOutside = new QVBoxLayout();
    QVBoxLayout * prevLayout = new QVBoxLayout();

    QHBoxLayout * headWidgetLayout = new QHBoxLayout();

    QHBoxLayout * imageLayout = new QHBoxLayout();


    QGroupBox *cardMenu = new QGroupBox();
    QGroupBox *footerMenu = new QGroupBox();

    QHBoxLayout * footerLayout = new QHBoxLayout(footerMenu);

    QFrame * line1 =  new QFrame();
    line1->setFrameShape(QFrame::HLine);
    QFrame * line2 =  new QFrame();
    line2->setFrameShape(QFrame::HLine);
    QFrame * line3 =  new QFrame();
    line3->setFrameShape(QFrame::HLine);
    QFrame * line4 =  new QFrame();
    line4->setFrameShape(QFrame::HLine);

    line1 -> setLineWidth(10);
    line1 -> setFixedHeight(6);
    line1->setStyleSheet("background-color: #1c1c1c;border-radius: 2px;border : 1px solid #1c1c1c");
    line2 -> setLineWidth(10);
    line2 -> setFixedHeight(6);
    line2 ->setStyleSheet("background-color: #1c1c1c;border-radius: 2px;border : 1px solid #1c1c1c");
    line3 -> setLineWidth(10);
    line3 -> setFixedHeight(6);
    line3->setStyleSheet("background-color: #1c1c1c;border-radius: 2px;border : 1px solid #1c1c1c");
    line4 -> setLineWidth(10);
    line4 -> setFixedHeight(6);
    line4 ->setStyleSheet("background-color: #1c1c1c;border-radius: 2px;border : 1px solid #1c1c1c");

    cardLayout = new QHBoxLayout(cardMenu);
    image = new QLabel();
    rightImage = new ClickableLabel();
    leftImage = new ClickableLabel();
    title = new QLabel();

    QLabel * nextTitle = new QLabel("Next Card");
    QLabel * PrevTitle = new QLabel("Prev Card");

    QLabel * current = new QLabel();
    QPixmap groundImg("asset/Icon/pointer.png");
    current -> setPixmap(groundImg);

    current ->setMargin(-22);


    title->setObjectName("Title");
    PrevTitle->setObjectName("TextNewDeck");
    nextTitle->setObjectName("TextNewDeck");
    PrevTitle-> setAlignment(Qt::AlignCenter);
    nextTitle->setAlignment(Qt::AlignCenter);
    current->setAlignment(Qt::AlignCenter);
    cardLayoutOutside->setAlignment(Qt::AlignCenter);
    QPushButton * backButton = new QPushButton("Back");
    deleteCard = new QPushButton("Delete");
    exportPNG = new QPushButton("Export PNG");
    modifyCard = new QPushButton("Modify");

    deleteCard ->setObjectName("remButton");
    exportPNG ->setObjectName("saveButton");
    modifyCard ->setObjectName("addButton");

    headWidgetLayout->addWidget(backButton);
    headWidgetLayout->addSpacing(20);
    headWidgetLayout->addWidget(title, 0, Qt::AlignRight);
    headLayout->addLayout(headWidgetLayout);
    headLayout->addStretch();

    cardLayout -> addWidget(image);
    cardLayout -> setContentsMargins(0,0,0,0);
    nextLayout -> setContentsMargins(0,0,0,0);
    prevLayout -> setContentsMargins(0,0,0,0);

    nextLayout -> addStretch();
    nextLayout -> addWidget(nextTitle);
    nextLayout -> addWidget(line1);
    nextLayout -> addWidget(rightImage);
    nextLayout -> addWidget(line2);
    nextLayout -> addStretch();

    prevLayout -> addStretch();
    prevLayout -> addWidget(PrevTitle);
    prevLayout -> addWidget(line3);
    prevLayout -> addWidget(leftImage);
    prevLayout -> addWidget(line4);
    prevLayout -> addStretch();

    cardLayoutOutside -> addWidget(current);
    cardLayoutOutside -> addWidget(cardMenu);
    cardLayoutOutside -> addStretch();

    imageLayout-> addStretch();
    imageLayout->addLayout(prevLayout);
    imageLayout-> addStretch();
    imageLayout->addLayout(cardLayoutOutside);
    imageLayout-> addStretch();
    imageLayout->addLayout(nextLayout);
    imageLayout->addStretch();

    headLayout->addLayout(imageLayout);
    headLayout->addStretch();
    image->setAlignment(Qt::AlignCenter);

    footerLayout->addStretch();
    footerLayout->addWidget(deleteCard);
    footerLayout->addWidget(modifyCard);
    footerLayout->addWidget(exportPNG);
    footerLayout->addStretch();

    headLayout->addWidget(footerMenu);



    backButton -> setFixedSize(155, 75);
    deleteCard->setFixedSize(200, 60);
    exportPNG->setFixedSize(200, 60);
    modifyCard->setFixedSize(200, 60);
    cardMenu ->setFixedSize(390,625);

    deleteCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    exportPNG->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    modifyCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(backButton, &QPushButton::clicked, this, &CardInfoPage::BackShowDeckPageSlot);
    connect(deleteCard, &QPushButton::clicked, this, &CardInfoPage::deleteCardSlot);
    connect(exportPNG, &QPushButton::clicked, this, &CardInfoPage::ExportPNGSlot);
    connect(rightImage, &ClickableLabel::clicked, this, &CardInfoPage::nextImageSlot);
    connect(leftImage, &ClickableLabel::clicked, this, &CardInfoPage::previousImageSlot);
    connect(modifyCard, &QPushButton::clicked, this, &CardInfoPage::modifyCardSlot);
}


void CardInfoPage::setPixmapp(Card* card) {
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
    deleteCard->show();
    exportPNG->show();
    if (curr) {
        cardSelected = curr;
        QSize size(296, 480);
        QString imagePath = QString::fromStdString(cardSelected->getUrl());
        QPixmap newPixmap(imagePath);
        if (newPixmap.isNull()) {
            image->clear();
        } else {
            image->setPixmap(newPixmap.scaled(370, 600, Qt::KeepAspectRatio));
            if (deck->next(cardSelected)) {
                QString nextImagePath = QString::fromStdString(deck->next(cardSelected)->getUrl());
                QPixmap nextPixmap(nextImagePath);
                rightImage->setPixmap(nextPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
            if (deck->prec(cardSelected)) {
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
        if(deck->size() == 1){
            deck->removeElement(cardSelected);
            rightImage->clear();
            leftImage->clear();

            emit BackShowDeckPageSignal();
            emit LastCardEliminatedSignal();
        }else{
            Card* nextCard = deck->next(cardSelected);
            deck->removeElement(cardSelected);
            cardSelected = nullptr;
            if (nextCard) {
                updateImage(nextCard);
                cardSelected = nextCard;
            } else {
                rightImage->clear();
                leftImage->clear();
            }


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
