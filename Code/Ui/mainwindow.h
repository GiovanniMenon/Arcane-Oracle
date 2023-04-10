#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "HomePage/manualdeck.h"
#include "HomePage/homepage.h"
#include "HomePage/newdeckpage.h"
#include "HomePage/loadpage.h"

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

public slots:
    void manualWindowSlot();
    void newDeckWindowSlot();
    void BackWindowSlot();
    void LoadDeckPageSlot();
signals:
    void newDeckWindowSignal();
    void manualWindowSignal();


};
#endif // MAINWINDOW_H
