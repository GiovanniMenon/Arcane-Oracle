#include "monsterwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

monsterwidget::monsterwidget(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout * main  = new QVBoxLayout(this);

    QHBoxLayout * Head = new QHBoxLayout();
    QLabel * label = new QLabel("Mostro");



    main -> addLayout(Head);
    main -> addWidget(label);




}
