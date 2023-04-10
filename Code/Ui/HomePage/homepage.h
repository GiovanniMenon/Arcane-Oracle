#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget * parent=nullptr);
public slots:
    void ManualHomePageSlot();
    void NewDeckPageSlot();
    void LoadDeckPageSlot();
signals :
    void ManualHomePageSignal();
    void NewDeckPageSignal();
    void LoadDeckPageSignal();

};

#endif // HOMEPAGE_H
