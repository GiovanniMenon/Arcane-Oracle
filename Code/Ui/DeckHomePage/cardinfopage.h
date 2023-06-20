#ifndef CARDINFOPAGE_H
#define CARDINFOPAGE_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>

#include "clickablelabel.h"
#include "../../class/Deck/deck.h"




class CardInfoPage : public QWidget
{
    Q_OBJECT
public:
    CardInfoPage(QWidget * parent=nullptr);
    void setPixmapp(Card* path);
    void updateImage(Card* curr);
public slots:
    void BackShowDeckPageSlot();

    void nextImageSlot();
    void previousImageSlot();

    void ExportPNGSlot();
    void deleteCardSlot();
    void modifyCardSlot();
    void saveDeckAfterModifySlot();

    void currentDeckSlot(Deck* currDeck);
    void receiveImagePaths(QStringList& imagePaths);
    void refreshImageSlot(Card* modified);
signals :

    void BackShowDeckPageSignal();
    void LastCardEliminatedSignal();
    void refreshDeckSignal();
    void modifyCardSignal(Card* toModify);
    void passDeckToVisitorSignal(Deck* d);
private:
    QLabel *image;
    QLabel* title;

    Deck* deck;
    Card* cardSelected;
    QDir* dir;

    ClickableLabel * rightImage;
    ClickableLabel * leftImage;

    int currentIndex;
    QStringList paths;
    QString currPath;

    QPushButton * deleteCard;
    QPushButton * exportPNG;
    QPushButton * modifyCard;

    QHBoxLayout * cardLayout;

};

#endif
