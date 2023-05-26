#ifndef CARDPAGE_H
#define CARDPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QFileDialog>

#include "../Visitor/cardwidget.h"
#include "../../class/Deck/deck.h"


class CardPage : public QWidget
{
    Q_OBJECT
public:
    CardPage(QWidget * parent=nullptr);
    void setCard(Card *);

public slots:
    void onGenerateCardFinish();
    void NewCardIdSlot(Deck*,QWidget*);
    void BackHomePageSlot();

    //Slot Dei pulsanti
    void AddNewCardSlot();
    void RemoveCardSlot();
    void generateCardSlot();
    void SaveScreenSlot();
    void ManualScreeSlot();

    //Slot Per la Modifica
    void ModifyCardSlot(Card* toModify);
    void BackShowDeckPageSlot();
    void SaveDeckAfterModifySlot();
    void RefreshImageSlot();

signals:
    void BackHomePageSignal();
    void BackBackHomePageSignal();
    void BackShowDeckPageSignal();

    void ModifiedCardSignal();
    void saveDeckAfterModifySignal();
    void refreshImageModifiedSignal(Card* modified);
private:
    Deck *deck;
    QWidget* absCard;

    QVBoxLayout *main;
    QHBoxLayout * card;

    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *CardManual;
    QPushButton *removeButton;
    QPushButton *addButton;
    QPushButton *backButton;


    QLabel *errore;

    Card* c;





};

#endif // CARDPAGE_H
