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
#include <QLineEdit>
#include <QScrollArea>
#include <QGridLayout>
#include <QFileInfo>
#include <QDirIterator>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>

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

    void saveDeckSlot();
    void lastCardDeletedSlot();
    void refreshDeckSlot();

    void sortByNameAscending();
    void sortByCostAscending();
    void sortByNameDescending();
    void sortByCostDescending();

    void searchTextDeck(const QString& text);
    void currentDeckSlot(Deck* currDeck);
    void imageClikedSlot(Card* card);
    void filterSlot();
    void deleteFilterSlot();

signals:
    void BackDeckPageSignal();
    void CardInfoSignal(Card* path, QDir* dir);
    void ImagePathsSignal(QStringList& imagePaths);
    void CurrentDeckSignal(Deck* currDeck);
private:
    int filterObj;
    QStringList filePathCards;
    QString nameDeck;

    Deck* deck;
    Deck* sortedDeck;

    QDir dir;
    QScrollArea *scrollArea;
    QWidget *imagesContainer;

    ClickableLabel* label;
    QLabel* imageLabel;

    QVBoxLayout *layout;
    QGridLayout *imagesLayout;
    QHBoxLayout *Head;
    QHBoxLayout *footer;
    QPushButton *saveDeck;

    QLabel* sadFace;
    QLabel* stillNoCard;

    QPushButton *sortByNameAsc;
    QPushButton *sortByCostAsc;
    QPushButton *sortByNameDesc;
    QPushButton *sortByCostDesc;

    QPushButton *deleteFilter;
    QPushButton *filter;

    bool sortByNameAscVisible;
    bool sortByNameDescVisible;
    bool sortByCostAscVisible;
    bool sortByCostDescVisible;

};

#endif // SHOWDECKPAGE_H
