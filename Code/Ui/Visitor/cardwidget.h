#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QIntValidator>
#include <QLabel>
#include <QSpinBox>
#include "../Utils/clickablelabel.h"
#include "../../class/Cards/abstractcard.h"
#include "../../class/Deck/deck.h"

class cardWidget : public QWidget
{
    Q_OBJECT
public:
    cardWidget(Deck *,QWidget *parent=nullptr);
    virtual Card* getInput() = 0;\
    virtual void generate() ;
    virtual bool checkInput() const;
    QPixmap takeScreen(bool i) const;
    std::string getUrl() const{
            return path;
    }
    void takeScreen(Card* c);

public slots:
    virtual void setFieldsCardSlot();
protected:
    Deck *deck;
    std::string path;

    QHBoxLayout *main;
    QVBoxLayout *inside;
    QHBoxLayout*  outside;
    QVBoxLayout*  outsideVertical;
    QHBoxLayout *centerImage;
    QVBoxLayout *imageLayout;

    QGroupBox *cardGroup;
    QLabel *loading;
    QMovie *gif ;
    QPixmap scaledPixmap;


    //Campi Carta
    QLabel *imageLabel;
    QLineEdit *nameCard;
    QLineEdit *costCard;
    QGroupBox *image;

    //Descrizione
    QTextEdit *desc;
    QString descText;

    //visitor
    Card* card;



};

#endif // CARDWIDGET_H
