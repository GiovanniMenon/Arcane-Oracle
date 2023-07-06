#include "showdeckpage.h"

ShowDeckPage::ShowDeckPage(QWidget * parent) : QWidget(parent), sortByNameAscVisible(true), sortByNameDescVisible(false), sortByCostAscVisible(true), sortByCostDescVisible(false) /*lastClickedLabel(nullptr)*/ {
    filterObj = 1;
    layout = new QVBoxLayout(this);
    imagesLayout = new QGridLayout();

    Head = new QHBoxLayout();
    QPushButton * backButton = new QPushButton("Back");
    sortByNameAsc = new QPushButton();
    sortByCostAsc = new QPushButton();
    sortByNameDesc = new QPushButton();
    sortByCostDesc = new QPushButton();
    filter = new QPushButton();
    deleteFilter = new QPushButton();
    QLineEdit *search = new QLineEdit(this);


    QPixmap p1("asset/Icon/AtoZ.png");
    QPixmap p2("asset/Icon/ZtoA.png");
    QPixmap p3("asset/Icon/1to9.png");
    QPixmap p4("asset/Icon/9to1.png");

    QPixmap p5("asset/Icon/filterM.png");
    QPixmap p6("asset/Icon/reset.png");

    QSize size(24, 24);
    p1 = p1.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2 = p2.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p3 = p3.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p4 = p4.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p5 = p5.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p6 = p6.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    sortByNameAsc->setIcon(p1);
    sortByNameDesc->setIcon(p2);
    sortByCostAsc->setIcon(p3);
    sortByCostDesc->setIcon(p4);
    sortByNameAsc->setIconSize(size);
    sortByNameDesc->setIconSize(size);
    sortByCostAsc->setIconSize(size);
    sortByCostDesc->setIconSize(size);


    filter->setIcon(p5);
    filter->setIconSize(size);
    deleteFilter->setIcon(p6);
    deleteFilter->setIconSize(size);

    search->setPlaceholderText("Search");
    search->setFixedSize(400,50);
    backButton -> setFixedSize(155, 75);
    sortByNameAsc-> setFixedSize(120, 50);
    sortByNameDesc-> setFixedSize(120, 50);
    sortByCostAsc-> setFixedSize(120, 50);
    sortByCostDesc-> setFixedSize(120, 50);

    filter -> setFixedSize(50, 50);
    deleteFilter-> setFixedSize(50, 50);


    deleteFilter -> setVisible(false);
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
    Head ->addWidget(sortByNameDesc);
    Head ->addWidget(sortByCostAsc);
    Head ->addWidget(sortByCostDesc);
    Head ->addWidget(deleteFilter);
    Head ->addWidget(filter);


    layout->addLayout(Head);


    scrollArea = new QScrollArea(this);

    imagesContainer = new QWidget();
    imagesLayout = new QGridLayout(imagesContainer);

    scrollArea->setWidget(imagesContainer);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);

    sortByNameAsc-> setObjectName("sortButtons");
    sortByNameDesc-> setObjectName("sortButtons");
    sortByCostAsc-> setObjectName("sortButtons");
    sortByCostDesc-> setObjectName("sortButtons");
    scrollArea ->setObjectName("scrollArea");
    imagesContainer ->setObjectName("ImageLayout");
    filter -> setObjectName("FilterButton");
    deleteFilter -> setObjectName("resetB");


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
    connect(filter, &QPushButton::clicked, this, &ShowDeckPage::filterSlot);
    connect(deleteFilter, &QPushButton::clicked, this, &ShowDeckPage::deleteFilterSlot);


}

void ShowDeckPage::filterSlot(){

    Deck* result = deck->filter(filterObj);
    clear();
    setPage(result);
    filterObj=((filterObj+1)%5)+1;
    std::string campo;
    switch (filterObj) {
    case 1:
        campo = "asset/Icon/filterM.png";
        break;
    case 2:
        campo = "asset/Icon/filterF.png";
        break;
    case 3:
        campo = "asset/Icon/filterA.png";
        break;
    case 4:
        campo = "asset/Icon/filterS.png";
        break;
    case 5:
        campo = "asset/Icon/filterT.png";
        break;

    default:
        campo = "asset/Icon/filterM.png";
        break;
    }
    QPixmap p7(campo.c_str());
    QSize size(24, 24);
    p7 = p7.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    filter->setIcon(p7);
    filter->setIconSize(size);
    deleteFilter -> setVisible(true);
}

void ShowDeckPage::deleteFilterSlot(){
    clear();
    setPage(deck);
    deleteFilter -> setVisible(false);
}

void ShowDeckPage::BackDeckPageSlot() {
    deleteFilter -> setVisible(false);
    dir.refresh();
    clear();
    emit BackDeckPageSignal();
}

void ShowDeckPage::currentDeckSlot(Deck * currDeck){
    deck = currDeck;
    sortedDeck = currDeck;
    nameDeck = QString::fromStdString(deck->getName());

    setPage(deck);
}


void ShowDeckPage::setPage(Deck* de) {

    dir = QDir("asset/Deck/" + nameDeck.replace(" ","") + "/Card");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    dir.setNameFilters(filters);

    if (dir.count() == 0) {
        //Deck vuoto
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
            connect(label, &ClickableLabel::clicked, this, [this, index = i, de ]() { imageClikedSlot((*de)[index]); });

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
        deleteFilter -> setVisible(false);
        ClickableLabel* clickedLabel = qobject_cast<ClickableLabel*>(sender()); // Ottiene il puntatore alla label cliccata
        QPixmap pixmap = clickedLabel->pixmap(Qt::ReturnByValue).scaled(500, 500, Qt::KeepAspectRatio);

        imageLabel = new QLabel();

        imageLabel->setPixmap(pixmap);
        emit CardInfoSignal(card, &dir);
        emit CurrentDeckSignal(deck);
}

void ShowDeckPage::saveDeckSlot(){
    QMessageBox msgBox;
    msgBox.setText("Salvataggio Mazzo");
    msgBox.setInformativeText("Il mazzo verra' salvato, rendendo permanenti tutte le modifiche effettuate. \nSei Sicuro?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        deck->save();
    }

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
    deleteFilter -> setVisible(false);
    sortedDeck->order(1, true);
    clear();
    setPage(sortedDeck);
    sortByNameAsc->setVisible(false);
    sortByNameDesc->setVisible(true);
    disconnect(sortByNameAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameAscending);
    connect(sortByNameDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameDescending);
}


void ShowDeckPage::sortByNameDescending() {
    deleteFilter -> setVisible(false);
    sortedDeck->order(1, false);
    clear();
    setPage(sortedDeck);
    sortByNameAsc->setVisible(true);
    sortByNameDesc->setVisible(false);
    disconnect(sortByNameDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameDescending);
    connect(sortByNameAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByNameAscending);
}



void ShowDeckPage::sortByCostAscending() {
    deleteFilter -> setVisible(false);
    sortedDeck->order(2, true);
    clear();
    setPage(sortedDeck);
    sortByCostAsc->setVisible(false);
    sortByCostDesc->setVisible(true);
    disconnect(sortByCostAsc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostAscending);
    connect(sortByCostDesc, &QPushButton::clicked, this, &ShowDeckPage::sortByCostDescending);
}

void ShowDeckPage::sortByCostDescending() {
    deleteFilter -> setVisible(false);
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
}





