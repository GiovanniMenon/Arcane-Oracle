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
public slots:
    void BackHomePageSlot();
    void GenerateCardSlot();

    void newDeckCreatedSlot(QString nome);
signals :
    void BackHomePageSignal();
    void GenerateCardSignal();
private :
    QVBoxLayout * layout ;
    QGroupBox * ButtonMenu;
    QGroupBox * LastCard;
    QString NomeMazzo;
    Deck deck;
    QLabel *nome1;

};

#endif // HOMEDECKPAGE_H
