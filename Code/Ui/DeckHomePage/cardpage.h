#ifndef CARDPAGE_H
#define CARDPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QIcon>

#include "../Visitor/cardwidget.h"

#include "../../class/Deck/deck.h"


class CardPage : public QWidget
{
    Q_OBJECT
public:
    CardPage(QWidget * parent=nullptr);
    void setCard(Card *);

public slots:
    void NewCardIdSlot(Deck*,QWidget*);
    void BackHomePageSlot();
    void AddNewCardSlot();
    void RemoveCardSlot();
    void generateCardSlot();
    void SaveScreenSlot();

    void ModifyCardSlot(Card* toModify);
    void BackShowDeckPageSlot();
    void SaveDeckAfterModifySlot();

    void RefreshImageSlot();
signals:
    void BackHomePageSignal();
    void BackBackHomePageSignal();
    void ModifiedCardSignal();
    void BackShowDeckPageSignal();
    void saveDeckAfterModifySignal();

    void refreshImageModifiedSignal(Card* modified);


private:
    Deck *deck;
    QWidget* absCard;

    QVBoxLayout *main;
    QHBoxLayout * card;
    QPushButton *generateButton;

    QPushButton *saveButton ;
    QPushButton *removeButton ;
    QPushButton *addButton ;

    QLabel *errore;
    QPushButton *backButton;

    Card* c;





};

#endif // CARDPAGE_H
