#ifndef MONSTERWIDGET_H
#define MONSTERWIDGET_H

#include <QWidget>
#include "../../class/Cards/monstercard.h"

class monsterwidget : QWidget
{
    Q_OBJECT
public:
    monsterwidget(QWidget *parent=nullptr);
    monsterwidget(monsterCard) ;
};

#endif // MONSTERWIDGET_H
