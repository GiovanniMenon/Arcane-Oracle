#include "mainwindow.h"
#include "HomePage/homepage.h"
#include "../class/Deck/deck.h"

#include <QVBoxLayout>
#include <iostream>
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
    //Segnali HomePage
    connect(homepage,&HomePage::ManualHomePageSignal, this, &MainWindow::manualWindowSlot );
    connect(homepage,&HomePage::NewDeckPageSignal, this, &MainWindow::newDeckWindowSlot );
    connect(homepage,&HomePage::LoadDeckPageSignal, this , &MainWindow::LoadDeckPageSlot );

    //BackSignal HomePage
    connect(manualdeck,&ManualDeck::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(newdeckpage,&NewDeckPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(loadpage,&LoadPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(homedeckpage,&HomeDeckPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(cardpage,&CardPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(typepage,&TypePage::BackDeckPageSignal, this , &MainWindow::BackWindowSlot );
    connect(showdeckpage, &ShowDeckPage::BackDeckPageSignal, this, &MainWindow::BackWindowSlot);

    //Doppio Back
    connect(cardpage,&CardPage::BackBackHomePageSignal, this , &MainWindow::BackBackWindowSlot );

    connect(newdeckpage,&NewDeckPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );
    connect(loadpage,&LoadPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );

    connect(homedeckpage, &HomeDeckPage::ShowDeckSignal, this, &MainWindow::ShowDeckPageSlot);
    connect(homedeckpage, &HomeDeckPage::GenerateCardSignal,this,&MainWindow::TypePageSlot);
    connect(typepage, &TypePage::CreateCardPageSignal,this,&MainWindow::CardPageSlot);
    connect(newdeckpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));
    connect(loadpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));
    connect(showdeckpage, &ShowDeckPage::CardInfoSignal, this, &MainWindow::CardInfoPageSlot);
    connect(cardinfopage, &CardInfoPage::BackShowDeckPageSignal, this,&MainWindow::BackWindowSlot);
    connect(cardinfopage, &CardInfoPage::BackShowDeckPageSignal, showdeckpage, &ShowDeckPage::refreshDeckSlot);
    connect(homedeckpage, SIGNAL(DeckSelectedSignal(Deck*)), showdeckpage, SLOT(currentDeckSlot(Deck*)));
    connect(homedeckpage, SIGNAL(DeckSelectedSignal(Deck*)), typepage, SLOT(currentDeckSlot(Deck*)));
    connect(showdeckpage, SIGNAL(CurrentDeckSignal(Deck*)), cardinfopage, SLOT(currentDeckSlot(Deck*)));
    connect(showdeckpage, SIGNAL(ImagePathsSignal(QStringList&)), cardinfopage, SLOT(receiveImagePaths(QStringList&)));
    connect(typepage, SIGNAL(CardSignal(Deck*,QWidget*)), cardpage, SLOT(NewCardIdSlot(Deck*,QWidget*)));
    stackedWidget -> setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::manualWindowSlot() {
    stackedWidget -> addWidget(manualdeck);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::BackWindowSlot() {
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

void MainWindow::CardInfoPageSlot(QPixmap* pixmap, Card* card){
    stackedWidget->addWidget(cardinfopage);
    cardinfopage->setPixmapp(pixmap,card);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);

}
