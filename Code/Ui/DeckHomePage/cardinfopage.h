#ifndef CARDINFOPAGE_H
#define CARDINFOPAGE_H
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "clickablelabel.h"

#include "../../class/Deck/deck.h"




class CardInfoPage : public QWidget
{
    Q_OBJECT
public:
    CardInfoPage(QWidget * parent=nullptr);
    void setPixmapp(QPixmap* pixmap, Card* path);
    void updateImage(Card* curr);
public slots:
    void BackShowDeckPageSlot();
    void ExportPNGSlot();
    void currentDeckSlot(Deck* currDeck);
    void nextImageSlot();
    void previousImageSlot();
    void receiveImagePaths(QStringList& imagePaths);
    void deleteCardSlot();

    void modifyCardSlot();
    void saveDeckAfterModifySlot();
    void refreshImageSlot(Card* modified);
signals :
    void BackShowDeckPageSignal();
    void LastCardEliminatedSignal();
    void refreshDeckSignal();
    void modifyCardSignal(Card* toModify);
    void passDeckToVisitorSignal(Deck* d);
private:
    QLabel *image;
    QPixmap* pixmap;
    QHBoxLayout* layout;
    QLabel* title;
    Deck* deck;
    ClickableLabel * rightImage;
    ClickableLabel * leftImage;
    int currentIndex;
    QStringList paths;
    QString currPath;
    Card* cardSelected;
    QPushButton * deleteCard;
    QPushButton * exportPNG;
    QPushButton * modifyCard;
    QDir* dir;


};

#endif
