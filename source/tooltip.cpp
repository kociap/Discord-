#include "QPainter"
#include "QTimer"
#include "driftuistyle.hpp"
#include "tooltip.hpp"

ToolTip::ToolTip(QWidget* parent, QWidget* target, const QString& text) : QWidget{parent}, text{text} {
    auto rc = target->rect();
    move(rc.center().x(), rc.top());

    repaint();

    //QTimer::singleShot(/* 7 second timeout */ 7000, [this]() { deleteLater(); });
}

QSize ToolTip::sizeHint() const {
    return QSize{QFontMetrics{QFont{}}.width(text) + 10, QFontMetrics{QFont{}}.height() + 10};
}

void ToolTip::paintEvent(QPaintEvent* ev) {
    QPainter painter{this};

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    auto rc = rect();

    QBrush brush;
    brush.setColor(QColor::fromRgb(0, 0, 0, 150));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRoundedRect(rc.marginsRemoved(QMargins{0, 0, 0, 10}), 5, 5, Qt::AbsoluteSize);

    painter.setBrush(DriftUIStyle::Dark[UIColor::Text]);

    painter.setFont(QFont{});
    painter.drawText(rc, text, QTextOption{Qt::AlignCenter});
}