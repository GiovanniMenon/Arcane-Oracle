#ifndef TYPEPAGE_H
#define TYPEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>


class TypePage : public QWidget
{
    Q_OBJECT
public:
    TypePage(QWidget * parent=nullptr);
public slots:
    void BackDeckPageSlot();
    void CardSlot();

signals:
    void CardSignal(int );
    void CreateCardPageSignal();
    void BackDeckPageSignal();
private:
     QVBoxLayout * layout;
     QLabel * DescText;
     QGroupBox * ButtonMenu;
     std::vector < QString> Descrizioni;
     bool eventFilter(QObject* obj, QEvent* event) ;




};

#endif // TYPEPAGE_H
