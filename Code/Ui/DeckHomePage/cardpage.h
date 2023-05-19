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

public slots:
    void NewCardIdSlot(Deck*,QWidget*);
    void BackHomePageSlot();
    void AddNewCardSlot();
    void RemoveCardSlot();
    void generateCardSlot();
    void SaveScreenSlot();
signals:
    void BackHomePageSignal();
    void BackBackHomePageSignal();



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





};

#endif // CARDPAGE_H
