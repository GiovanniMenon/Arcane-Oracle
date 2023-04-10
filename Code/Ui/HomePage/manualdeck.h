#ifndef MANUALDECK_H
#define MANUALDECK_H

#include <QWidget>

class ManualDeck : public QWidget
{
Q_OBJECT
public:
    ManualDeck(QWidget *parent=nullptr);
public slots:
    void BackHomePageSlot();

signals :
    void BackHomePageSignal();
};

#endif // MANUALDECK_H
