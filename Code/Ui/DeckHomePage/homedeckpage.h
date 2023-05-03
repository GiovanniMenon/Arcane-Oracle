#ifndef HOMEDECKPAGE_H
#define HOMEDECKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class HomeDeckPage : public QWidget
{
Q_OBJECT
public:
    HomeDeckPage(QWidget * parent=nullptr);
public slots:
    void BackHomePageSlot();
signals :
    void BackHomePageSignal();
private :
    QString NomeMazzo;
};

#endif // HOMEDECKPAGE_H
