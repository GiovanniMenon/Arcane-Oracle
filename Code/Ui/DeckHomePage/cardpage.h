#ifndef CARDPAGE_H
#define CARDPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CardPage : public QWidget
{
    Q_OBJECT
public:
    CardPage();

public slots:
    void NewCardIdSlot(int);


private:
    QVBoxLayout *main;




};

#endif // CARDPAGE_H
