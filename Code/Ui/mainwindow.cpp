#include "mainwindow.h"
#include "HomePage/homepage.h"

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
    cardpage = new CardPage();




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

    //Back Signal Normale
    connect(cardpage,&CardPage::BackDeckPageSignal, this , &MainWindow::BackWindowSlot );

    connect(newdeckpage,&NewDeckPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );
    connect(loadpage,&LoadPage::HomeDeckPageSignal, this , &MainWindow::HomeDeckPageSlot );

    connect(homedeckpage, &HomeDeckPage::GenerateCardSignal,this,&MainWindow::CardPageSlot);

    connect(newdeckpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));
    connect(loadpage, SIGNAL(newDeckCreatedSignal(QString)), homedeckpage, SLOT(newDeckCreatedSlot(QString)));

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

void MainWindow::CardPageSlot() {
    stackedWidget -> addWidget(cardpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}


