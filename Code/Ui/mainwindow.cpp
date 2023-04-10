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
    setCentralWidget(stackedWidget);

    stackedWidget -> addWidget(homepage);

    connect(homepage,&HomePage::ManualHomePageSignal, this, &MainWindow::manualWindowSlot );
    connect(homepage,&HomePage::NewDeckPageSignal, this, &MainWindow::newDeckWindowSlot );
    connect(homepage,&HomePage::LoadDeckPageSignal, this , &MainWindow::LoadDeckPageSlot );

    connect(manualdeck,&ManualDeck::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(newdeckpage,&NewDeckPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
    connect(loadpage,&LoadPage::BackHomePageSignal, this , &MainWindow::BackWindowSlot );
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
    stackedWidget -> setCurrentIndex(0);
}

void MainWindow::newDeckWindowSlot() {
    stackedWidget -> addWidget(newdeckpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}

void MainWindow::LoadDeckPageSlot() {
    stackedWidget -> addWidget(loadpage);
    stackedWidget -> setCurrentIndex(stackedWidget->currentIndex()+1);
}
