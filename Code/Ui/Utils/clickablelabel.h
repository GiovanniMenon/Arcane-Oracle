#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <QtGui/qevent.h>


class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel( QString text = "", QWidget* parent = nullptr);
    ~ClickableLabel() = default;

signals:
    void clicked();

public slots:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif
