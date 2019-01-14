#ifndef TOOLTIP_HPP
#define TOOLTIP_HPP

#include "QWidget"

class ToolTip : public QWidget {
    Q_OBJECT

public:
    explicit ToolTip(QWidget* parent = 0, QWidget* target = 0, const QString& text = "");

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* ev) override;

private:
    QString text;
};

#endif