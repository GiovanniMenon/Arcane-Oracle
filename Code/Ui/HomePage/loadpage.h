#ifndef LOADPAGE_H
#define LOADPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <vector>
#include <QScrollArea>

class LoadPage : public QWidget{
Q_OBJECT
public:
    LoadPage(QWidget *parent = nullptr);
    void refresh();
public slots:
    void BackHomePageSlot();
    void HomeDeckPageSlot();
signals :
    void BackHomePageSignal();
    void HomeDeckPageSignal();
    void newDeckCreatedSignal(QString nome);
private:
    std::vector <std::string> NomiDeck;
    QButtonGroup *buttonGroup;
    QVBoxLayout *layout;
    QVBoxLayout *vbox;
    QGroupBox *groupBox;
    QScrollArea *scroll;

    QGroupBox *loadDeckGroup();
    void SearchDeck();


};

#endif // LOADPAGE_H
