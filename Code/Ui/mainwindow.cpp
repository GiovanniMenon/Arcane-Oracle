#include "mainwindow.h"
#include "HomePage/homepage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    stackedWidget = new QStackedWidget(this);

    homepage = new HomePage();
    manualdeck = new ManualDeck() ;
    newdeckpage = new NewDeckPage();
    loadpage = new LoadPage();
    homedeckpage = new HomeDeckPage();
    showdeckpage = new ShowDeckPage();
    typepage = new TypePage();
    cardpage = new CardPage();
    cardinfopage = new CardInfoPage();

    setCentralWidget(stackedWidget);
    stackedWidget -> addWidget(homepage);
    stackedWidget -> setCurrentIndex(0);

    //Segnali HomePage
    connect(homepage,&HomePage::ManualHomePageSignal, this, &MainWindow::manualWindowSlot );
    connect(homepage,&HomePage::NewDeckPageSignal, this, &MainWindow::newDeckWindowSlot );
    connect(homepage,&HomePage::LoadDeckPageSignal, this , &MainWindow::LoadDeckPageSlot );
    connect(homepage,&HomePage::lightmodeSignal, this , &MainWindow::modeSlot );

    //Segnali DeckHomePage
    connect(homedeckpage, &HomeDeckPage::ShowDeckSignal, this, &MainWindow::ShowDeckPageSlot);
    connect(homedeckpage, &HomeDeckPage::GenerateCardSignal,this,&MainWindow::TypePageSlot);
    connect(typepage, &TypePage::CreateCardPageSignal,this,&MainWindow::CardPageSlot);
    connect(showdeckpage, &ShowDeckPage::CardInfoSignal, this, &MainWindow::CardInfoPageSlot);

    //BackSignal HomePage
    connect(manualdeck,&ManualDeck::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(newdeckpage,&NewDeckPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(loadpage,&LoadPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(homedeckpage,&HomeDeckPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(cardpage,&CardPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(typepage,&TypePage::BackDeckPageSignal, this , &MainWindow::BackWindowSlot );
    connect(showdeckpage, &ShowDeckPage::BackDeckPageSignal, this, &MainWindow::BackWindowSlotHomePage);
    connect(cardinfopage, &CardInfoPage::BackShowDeckPageSignal, this,&MainWindow::BackWindowSlot);

    //Doppio Back
    connect(cardpage,&CardPage::BackBackHomePageSignal, this , &MainWindow::BackBackWindowSlot );

    connect(newdeckpage,&NewDeckPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );
    connect(loadpage,&LoadPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );



    connect(cardinfopage, &CardInfoPage::BackShowDeckPageSignal, showdeckpage, &ShowDeckPage::refreshDeckSlot);

    connect(newdeckpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));
    connect(loadpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));
    connect(homedeckpage, SIGNAL(DeckSelectedSignal(Deck*)), showdeckpage, SLOT(currentDeckSlot(Deck*)));
    connect(homedeckpage, SIGNAL(DeckSelectedSignal(Deck*)), typepage, SLOT(currentDeckSlot(Deck*)));
    connect(showdeckpage, SIGNAL(CurrentDeckSignal(Deck*)), cardinfopage, SLOT(currentDeckSlot(Deck*)));
    connect(showdeckpage, SIGNAL(ImagePathsSignal(QStringList&)), cardinfopage, SLOT(receiveImagePaths(QStringList&)));
    connect(typepage, SIGNAL(CardSignal(Deck*,QWidget*)), cardpage, SLOT(NewCardIdSlot(Deck*,QWidget*)));
    connect(cardpage, SIGNAL(refreshImageModifiedSignal(Card*)), cardinfopage, SLOT(refreshImageSlot(Card*)));
    connect(cardinfopage, SIGNAL(modifyCardSignal(Card*)), cardpage, SLOT(ModifyCardSlot(Card*)));


    connect(cardpage, &CardPage::ModifiedCardSignal, this, &MainWindow::CardPageSlot);
    connect(cardpage, &CardPage::saveDeckAfterModifySignal, cardinfopage, &CardInfoPage::saveDeckAfterModifySlot);

    connect(cardinfopage, &CardInfoPage::LastCardEliminatedSignal, showdeckpage, &ShowDeckPage::lastCardDeletedSlot);
    connect(cardpage, &CardPage::refreshImageModifiedSignal, cardinfopage, &CardInfoPage::refreshImageSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::modeSlot(int mode) {
    std::string path;

    switch (mode) {
    case 0:
        path = "asset/Light_style.qss";
        break;
    case 1:
        path =  "asset/Dark_style.qss";

        break;
    default:
        break;
    }

    QFile stylesheet(path.c_str());
    stylesheet.open(QFile::ReadOnly);
    setStyleSheet(QLatin1String(stylesheet.readAll()));

}

void MainWindow::manualWindowSlot() {
    stackedWidget -> addWidget(manualdeck);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::BackWindowSlot() {
    stackedWidget ->removeWidget(stackedWidget->currentWidget());
}
void MainWindow::BackWindowSlotHomePage() {
    homedeckpage -> lastCardGenerate() ;
    stackedWidget ->removeWidget(stackedWidget->currentWidget());
}
void MainWindow::BackBackWindowSlot() {
    homedeckpage -> lastCardGenerate() ;
    stackedWidget ->removeWidget(stackedWidget->currentWidget());
    stackedWidget ->removeWidget(stackedWidget->currentWidget());
}

void MainWindow::newDeckWindowSlot() {
    stackedWidget -> addWidget(newdeckpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::LoadDeckPageSlot() {
    loadpage -> refresh();
    stackedWidget -> addWidget(loadpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::HomeDeckPageSlot() {

    stackedWidget -> removeWidget(stackedWidget->currentWidget());
    stackedWidget -> addWidget(homedeckpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::ShowDeckPageSlot(){
    stackedWidget -> addWidget(showdeckpage);
    showdeckpage->clear();
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::TypePageSlot() {
    stackedWidget -> addWidget(typepage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}
void MainWindow::CardPageSlot() {
    stackedWidget -> addWidget(cardpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::CardInfoPageSlot(Card* card){
    stackedWidget->addWidget(cardinfopage);
    cardinfopage->setPixmapp(card);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

