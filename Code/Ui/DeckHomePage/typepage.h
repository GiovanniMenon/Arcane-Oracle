#ifndef TYPEPAGE_H
#define TYPEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

#include "../../class/Deck/deck.h"

class TypePage : public QWidget
{
    Q_OBJECT
public:
    TypePage(QWidget * parent=nullptr);
public slots:
    void BackDeckPageSlot();
    void CardSlot();
    void currentDeckSlot(Deck* currDeck);
signals:
    void CardSignal(Deck*, QWidget* );
    void CreateCardPageSignal();
    void BackDeckPageSignal();
private:
    Deck* deck;
    QVBoxLayout * layout;
    QLabel * DescText;
    QGroupBox * ButtonMenu;
    std::vector < QString> Descrizioni;
    std::vector < QWidget*> cardWidgets;
    bool eventFilter(QObject* obj, QEvent* event) ;




};

#endif // TYPEPAGE_H
