#ifndef HOMEDECKPAGE_H
#define HOMEDECKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include "../../class/Deck/deck.h"

class HomeDeckPage : public QWidget
{
Q_OBJECT
public:
    HomeDeckPage(QWidget * parent=nullptr);
    void lastCardGenerate() const;
public slots:
    void BackHomePageSlot();
    void GenerateCardSlot();
    void ShowDeckSlot();

    void newDeckCreatedSlot(QString nome);
signals :
    void BackHomePageSignal();
    void GenerateCardSignal();
    void ShowDeckSignal();
    void DeckSelectedSignal(Deck* currDeck);



private :

    QHBoxLayout * layout ;
    QGroupBox * ButtonMenu;
    QGroupBox * LastCard;
    QString NomeMazzo;
    Deck deck;
    QLabel *header;

};

#endif // HOMEDECKPAGE_H
