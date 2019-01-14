#include "servericonwidget.hpp"
#include "QPainter"

ServerIconWidget::ServerIconWidget(QWidget* parent) : ServerIconWidget("", parent) {}

ServerIconWidget::ServerIconWidget(const QString& name, QWidget* parent) : QWidget(parent), name{name} {}

QSize ServerIconWidget::sizeHint() const {
    return QSize{75, 75};
}

void ServerIconWidget::paintEvent(QPaintEvent* event) {
    QPainter painter{this};

    painter.setBrush(Qt::yellow);
    painter.drawRoundRect(rect(), 25, 25);
}
