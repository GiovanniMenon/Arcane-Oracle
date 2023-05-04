#ifndef HOMEDECKPAGE_H
#define HOMEDECKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../../class/Deck/deck.h"

class HomeDeckPage : public QWidget
{
Q_OBJECT
public:
    HomeDeckPage(QWidget * parent=nullptr);
public slots:
    void BackHomePageSlot();
    void newDeckCreatedSlot(QString nome);
signals :
    void BackHomePageSignal();
private :
    QVBoxLayout * layout ;
    QString NomeMazzo;
    Deck deck;
    QLabel *nome1;

};

#endif // HOMEDECKPAGE_H
