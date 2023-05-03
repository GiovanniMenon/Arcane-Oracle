#ifndef NEWDECKPAGE_H
#define NEWDECKPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
private :
    QLineEdit *DeckName;
    QVBoxLayout * layout;
};

#endif // NEWDECKPAGE_H
