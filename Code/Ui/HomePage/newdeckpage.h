#ifndef NEWDECKPAGE_H
#define NEWDECKPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
class NewDeckPage : public QWidget
{
Q_OBJECT
public:
    NewDeckPage(QWidget *parent = nullptr);

public slots:
    void BackHomePageSlot();
    void HomeDeckPageSlot();
signals :
    void BackHomePageSignal();
    void HomeDeckPageSignal();
};

#endif // NEWDECKPAGE_H
