#ifndef NEWDECKPAGE_H
#define NEWDECKPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class NewDeckPage : public QWidget
{
Q_OBJECT
public:
    NewDeckPage(QWidget *parent = nullptr);

public slots:
    void BackHomePageSlot();
    void HomeDeckPageSlot();

signals :
    void newDeckCreatedSignal(QString nome);
    void BackHomePageSignal();
    void HomeDeckPageSignal();
private :
    QLineEdit *DeckName;
    QVBoxLayout * layout;
    QLabel * Errore ;
};

#endif // NEWDECKPAGE_H
