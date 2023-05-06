#ifndef CARDPAGE_H
#define CARDPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>


class CardPage : public QWidget
{
    Q_OBJECT
public:
    CardPage(QWidget * parent=nullptr);
public slots:
    void BackDeckPageSlot();
signals:
    void BackDeckPageSignal();
private:
     QVBoxLayout * layout;
     QLabel * DescText;
     bool eventFilter(QObject* obj, QEvent* event) ;




};

#endif // CARDPAGE_H
