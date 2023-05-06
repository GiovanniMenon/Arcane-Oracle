#include "showdeckpage.h"
#include <QLineEdit>
#include <QDir>
#include <QScrollArea>
#include <QGridLayout>

ShowDeckPage::ShowDeckPage(QWidget * parent) : QWidget(parent){
    layout = new QVBoxLayout(this);

    QHBoxLayout * Head = new QHBoxLayout();
    QHBoxLayout * footer = new QHBoxLayout();

    QPushButton * backButton = new QPushButton("Back");

    backButton -> setFixedSize(155, 60);

    QPushButton * deleteCard = new QPushButton("Delete");
    QPushButton * sortCard = new QPushButton("Sort");
    QPushButton * saveDeck = new QPushButton("Save");
    QPushButton * savePNG = new QPushButton("Save PNG");

    l1 = new QLabel();
    l2 = new QLabel();



    QLineEdit *search = new QLineEdit(this);
    search->setPlaceholderText("Search");
    search->setFixedHeight(30);

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *imagesContainer = new QWidget();
    imagesLayout = new QGridLayout(imagesContainer);

    // Leggi i file nella cartella delle immagini
    QDir dir("asset/images");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();

    int row = 0;
    int col = 0;
    for (const QFileInfo &fileInfo : fileList) {
        QPixmap pixmap(fileInfo.absoluteFilePath());
        QLabel *label = new QLabel();
        label->setPixmap(pixmap);
        label->setScaledContents(true);
        label->setFixedSize(200, 200);

        imagesLayout->addWidget(label, row, col);

        col++;
        if (col >= 4) {
            col = 0;
            row++;
        }
    }

    scrollArea->setWidget(imagesContainer);
    scrollArea->setWidgetResizable(true);

    Head -> addWidget(backButton);
    Head -> addStretch();
    Head -> addWidget(search);
    Head -> addStretch();
    Head->addWidget(l1);
    Head->addWidget(l2);
    Head -> addWidget(sortCard);


    footer->addWidget(savePNG);
    Head -> addStretch();
    footer->addWidget(saveDeck);
    Head -> addStretch();
    footer->addWidget(deleteCard);
    Head -> addStretch();


    layout->addLayout(Head);
    //layout->addWidget(scrollArea);
    layout->addLayout(footer);


    connect(backButton,&QPushButton::clicked, this ,&ShowDeckPage::BackDeckPageSlot);

}

void ShowDeckPage::BackDeckPageSlot() {
    emit BackDeckPageSignal();
}


void ShowDeckPage::currentDeckSlot(Deck * currDeck){
    deck = currDeck;

}




