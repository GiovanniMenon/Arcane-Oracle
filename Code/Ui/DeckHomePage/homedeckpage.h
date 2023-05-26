#ifndef HOMEDECKPAGE_H
#define HOMEDECKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QLabel>
#include <QDir>
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
    void DeleteDeckSlot();
    void newDeckCreatedSlot(QString nome);
signals :
    void BackHomePageSignal();
    void GenerateCardSignal();
    void ShowDeckSignal();
    void DeckSelectedSignal(Deck* currDeck);

private :

    QHBoxLayout * layout ;
    QVBoxLayout * lastCardLayout;
    QVBoxLayout *centerImage;

    QGroupBox * ButtonMenu;
    QGroupBox * LastCard;

    QString NomeMazzo;
    Deck deck;

    QLabel *header;
    QLabel* stillNoCard;
    QLabel* imageLabel;
    QLabel* sadFace;

};

#endif // HOMEDECKPAGE_H
