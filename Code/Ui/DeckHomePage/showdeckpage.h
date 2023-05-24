#ifndef SHOWDECKPAGE_H
#define SHOWDECKPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMessageBox>
#include <QDir>
#include "../Utils/clickablelabel.h"

#include "../../class/Deck/deck.h"
#include "../../class/Cards/abstractcard.h"


class ShowDeckPage : public QWidget
{
    Q_OBJECT
public:
    ShowDeckPage(QWidget *parent = nullptr);
    void setPage(Deck* d);
    void clear();
    void noCards();
public slots:
    void BackDeckPageSlot();
    void currentDeckSlot(Deck* currDeck);
    void imageClikedSlot(Card* card);
    void saveDeckSlot();
    void lastCardDeletedSlot();
    void refreshDeckSlot();


    void sortByNameAscending();
    void sortByCostAscending();
    void sortByNameDescending();
    void sortByCostDescending();
    void searchTextDeck(const QString& text);

signals:
    void BackDeckPageSignal();
    void CardInfoSignal(QPixmap* pixmap, Card* path, QDir* dir);
    void ImagePathsSignal(QStringList& imagePaths);
    void CurrentDeckSignal(Deck* currDeck);
private:
    QVBoxLayout * layout;
    Deck* deck;
    Deck* sortedDeck;
    QGridLayout *imagesLayout;
    QHBoxLayout * Head;
    QString nameDeck;
    QScrollArea *scrollArea;
    QWidget *imagesContainer;
    ClickableLabel* label;
    QLabel* imageLabel;
    QStringList filePathCards;
    QDir dir;

    QHBoxLayout* footer;
    QPushButton* saveDeck;
    QLabel* sadFace;
    QLabel* stillNoCard;

    QPushButton *sortByNameAsc;
    QPushButton *sortByCostAsc;
    QPushButton *sortByNameDesc;
    QPushButton *sortByCostDesc;

    bool sortByNameAscVisible;
    bool sortByNameDescVisible;
    bool sortByCostAscVisible;
    bool sortByCostDescVisible;

};

#endif // SHOWDECKPAGE_H
