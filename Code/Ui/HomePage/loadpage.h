#ifndef LOADPAGE_H
#define LOADPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
class LoadPage : public QWidget{
Q_OBJECT
public:
    LoadPage(QWidget *parent = nullptr);
public slots:
    void BackHomePageSlot();
signals :
    void BackHomePageSignal();
private:
    QGroupBox *loadDeckGroup();
};

#endif // LOADPAGE_H
