#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "HomePage/manualdeck.h"
#include "HomePage/homepage.h"
#include "HomePage/newdeckpage.h"
#include "HomePage/loadpage.h"
#include "DeckHomePage/homedeckpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainWindow *ui;
    QStackedWidget *stackedWidget;
    ManualDeck *manualdeck;
    HomePage *homepage;
    NewDeckPage *newdeckpage;
    LoadPage *loadpage;
    HomeDeckPage *homedeckpage;

public slots:
    void manualWindowSlot();
    void newDeckWindowSlot();
    void LoadDeckPageSlot();

    void BackWindowSlot();

    void HomeDeckPageSlot();
signals:
    void newDeckWindowSignal();
    void manualWindowSignal();


};
#endif // MAINWINDOW_H
