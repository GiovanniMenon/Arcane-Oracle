#include "showdeckpage.h"
#include <QLineEdit>
#include <QScrollArea>
#include <QGridLayout>
#include <QFileInfo>
#include <QDebug>
#include <QDirIterator>
#include <QMessageBox>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QFileDialog>

ShowDeckPage::ShowDeckPage(QWidget * parent) : QWidget(parent), sortByNameAscVisible(true), sortByNameDescVisible(false), sortByCostAscVisible(true), sortByCostDescVisible(false) /*lastClickedLabel(nullptr)*/ {
    layout = new QVBoxLayout(this);
    imagesLayout = new QGridLayout();

    Head = new QHBoxLayout();
    QPushButton * backButton = new QPushButton("Back");
    sortByNameAsc = new QPushButton();
    sortByCostAsc = new QPushButton();
    sortByNameDesc = new QPushButton();
    sortByCostDesc = new QPushButton();
    QLineEdit *search = new QLineEdit(this);


    QPixmap p1("asset/Icon/AtoZ.png");
    QPixmap p2("asset/Icon/ZtoA.png");
    QPixmap p3("asset/Icon/1to9.png");
    QPixmap p4("asset/Icon/9to1.png");
    QSize size(24, 24);
    p1 = p1.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2 = p2.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p3 = p3.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p4 = p4.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    sortByNameAsc->setIcon(p1);
    sortByNameDesc->setIcon(p2);
    sortByCostAsc->setIcon(p3);
    sortByCostDesc->setIcon(p4);
    sortByNameAsc->setIconSize(size);
    sortByNameDesc->setIconSize(size);
    sortByCostAsc->setIconSize(size);
    sortByCostDesc->setIconSize(size);


    /*sadFace = new QLabel("˙◠˙");
    sadFace->setObjectName("Title");
    stillNoCard = new QLabel("Still no cards saved");
    stillNoCard->setObjectName("GHeader");*/

    search->setPlaceholderText("Search");
    search->setFixedSize(400,50);
    backButton -> setFixedSize(155, 75);
    sortByNameAsc-> setFixedSize(120, 50);
    sortByNameDesc-> setFixedSize(120, 50);
    sortByCostAsc-> setFixedSize(120, 50);
    sortByCostDesc-> setFixedSize(120, 50);

    sortByNameAsc-> setObjectName("sortButtons");
    sortByNameDesc-> setObjectName("sortButtons");
    sortByCostAsc-> setObjectName("sortButtons");
    sortByCostDesc-> setObjectName("sortButtons");

    sortByNameDesc->setVisible(false);
    sortByCostDesc->setVisible(false);
    search->setAlignment(Qt::AlignCenter);


    Head -> addWidget(backButton);
    Head -> addStretch();
    Head -> addStretch();
    Head -> addWidget(search);
    Head -> addStretch(); 
    Head->addStretch();
    Head -> addWidget(sortByNameAsc);
    Head->addWidget(sortByNameDesc);
    Head->addWidget(sortByCostAsc);
    Head->addWidget(sortByCostDesc);

    layout->addLayout(Head);


    scrollArea = new QScrollArea(this);
    scrollArea ->setObjectName("scrollArea");
    imagesContainer = new QWidget();
    imagesLayout = new QGridLayout(imagesContainer);
    imagesContainer ->setObjectName("ImageLayout");
    scrollArea->setWidget(imagesContainer);
    scrollArea->setWidgetResizable(true);

    layout->addWidget(scrollArea);




    saveDeck = new QPushButton("Save");
    footer = new QHBoxLayout();
    layout->addLayout(footer);
    footer->addStretch();
    footer->addWidget(saveDeck);
    footer->addStretch();
    footer->setAlignment(Qt::AlignCenter);
    saveDeck->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    saveDeck->setFixedHeight(60);



    connect(backButton,&QPushButton::clicked, this ,&ShowDeckPage::BackDeckPageSlot);
    connect(saveDeck, &QPushButton::clicked, this, &ShowDeckPage::saveDeckSlot);
    connect(sortByNameAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameAscending);
    connect(sortByCostAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostAscending);
    connect(search, &QLineEdit::textChanged, this, &ShowDeckPage::searchTextDeck);


}

void ShowDeckPage::BackDeckPageSlot() {
    //lastClickedLabel = nullptr;
    dir.refresh();
    clear();
    emit BackDeckPageSignal();
}

void ShowDeckPage::currentDeckSlot(Deck * currDeck){
    deck = currDeck;
    sortedDeck = currDeck;
    nameDeck = QString::fromStdString(deck->getName());
    //dir.refresh();
    setPage(deck);
}


void ShowDeckPage::setPage(Deck* de) {

    // Leggi i file nella cartella delle immagini
    dir = QDir("asset/Deck/" + nameDeck + "/img");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    dir.setNameFilters(filters);
    //QFileInfoList fileList = dir.entryInfoList();

    if (dir.count() == 0) {
        //messaggio di deck vuoto
    }
    else {

        int row = 0;
        int col = 0;
        filePathCards.clear();
        QSize size(148,240);
        for (unsigned int i = 0; i < de->size(); i++) {
            QString path = QString::fromStdString(((*de)[i])->getUrl());

            QFileInfo fileInfo;
            fileInfo.setFile(path);
            QString filePath = fileInfo.filePath();
            QPixmap pixmap(filePath);
            label = new ClickableLabel();

            label->setEnabled(true);
            label->setMouseTracking(true);
            label->setPixmap(pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            label->setScaledContents(true);
            label->setFixedSize(148, 240);
            connect(label, &ClickableLabel::clicked, this, [this, index = i, de = deck]() { imageClikedSlot((*de)[index]); });

            imagesLayout->addWidget(label, row, col);

            col++;
            if (col >= 4) {
                col = 0;
                row++;
            }
        }
    }
    emit ImagePathsSignal(filePathCards);
}


void ShowDeckPage::imageClikedSlot(Card* card) {
        ClickableLabel* clickedLabel = qobject_cast<ClickableLabel*>(sender()); // Ottiene il puntatore alla label cliccata
        QPixmap pixmap = clickedLabel->pixmap().scaled(500, 500, Qt::KeepAspectRatio);

        imageLabel = new QLabel();

        imageLabel->setPixmap(pixmap);
        emit CardInfoSignal(&pixmap, card, &dir);
        emit CurrentDeckSignal(deck);


}

void ShowDeckPage::saveDeckSlot(){
    deck->save();
}

void ShowDeckPage::clear() {
    int rowCount = imagesLayout->rowCount();
    int colCount = imagesLayout->columnCount();

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            QLayoutItem* item = imagesLayout->itemAtPosition(row, col);
            if (item) {
                QWidget* widget = item->widget();
                if (widget) {
                    imagesLayout->removeWidget(widget);
                    delete widget;
                }
            }
        }
    }
}






void ShowDeckPage::noCards(){
    QLabel* sadFace = new QLabel("˙◠˙");
    sadFace->setObjectName("Title");
    QLabel* stillNoCard = new QLabel("Still no cards saved");
    stillNoCard->setObjectName("GHeader");
    layout->addStretch();
    layout->addWidget(sadFace);
    layout->addWidget(stillNoCard);
    layout->addStretch();
    sadFace->setAlignment(Qt::AlignCenter);
    stillNoCard->setAlignment(Qt::AlignCenter);

    // Aggiungi questo codice per centrare il layout nella finestra
    imagesLayout->setAlignment(Qt::AlignCenter);
}


void ShowDeckPage::lastCardDeletedSlot(){
    clear();
    setPage(deck);
}

void ShowDeckPage::refreshDeckSlot(){
    clear();
    setPage(deck);
}

void ShowDeckPage::sortByNameAscending() {
    sortedDeck->order(1, true);
    clear();
    setPage(sortedDeck);
    sortByNameAsc->setVisible(false);
    sortByNameDesc->setVisible(true);
    disconnect(sortByNameAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameAscending);
    connect(sortByNameDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameDescending);
}


void ShowDeckPage::sortByNameDescending() {
    sortedDeck->order(1, false);
    clear();
    setPage(sortedDeck);
    sortByNameAsc->setVisible(true);
    sortByNameDesc->setVisible(false);
    disconnect(sortByNameDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameDescending);
    connect(sortByNameAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameAscending);
}



void ShowDeckPage::sortByCostAscending() {
    sortedDeck->order(2, true);
    clear();
    setPage(sortedDeck);
    sortByCostAsc->setVisible(false);
    sortByCostDesc->setVisible(true);
    disconnect(sortByCostAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostAscending);
    connect(sortByCostDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostDescending);
}

void ShowDeckPage::sortByCostDescending() {
    sortedDeck->order(2, false);
    clear();
    setPage(sortedDeck);
    sortByCostAsc->setVisible(true);
    sortByCostDesc->setVisible(false);
    disconnect(sortByCostDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostDescending);
    connect(sortByCostAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostAscending);
}

void ShowDeckPage::searchTextDeck(const QString& text){
    std::string texToSearch = text.toStdString();

    Deck* result = deck->search(texToSearch);
    clear();
    setPage(result);
    delete result;

}





