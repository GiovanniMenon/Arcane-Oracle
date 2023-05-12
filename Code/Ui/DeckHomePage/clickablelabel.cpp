#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QString text, QWidget* parent) : QLabel(text,parent) {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
}
