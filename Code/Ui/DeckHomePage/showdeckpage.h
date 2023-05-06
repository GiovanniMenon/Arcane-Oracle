#ifndef SHOWDECKPAGE_H
#define SHOWDECKPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "../../class/Deck/deck.h"


class ShowDeckPage : public QWidget
{
    Q_OBJECT
public:
    ShowDeckPage(QWidget *parent = nullptr);
public slots:
    void BackDeckPageSlot();
    void currentDeckSlot(Deck* currDeck);
signals:
    void BackDeckPageSignal();
private:
    QVBoxLayout * layout;
    Deck* deck;
    QLabel* l1;
    QLabel* l2;
    QGridLayout *imagesLayout;
};

#endif // SHOWDECKPAGE_H
