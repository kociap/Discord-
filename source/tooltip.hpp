#ifndef TOOLTIP_HPP
#define TOOLTIP_HPP

#include "QWidget"

class ToolTip : public QWidget {
    Q_OBJECT

public:
    explicit ToolTip(QWidget* parent = nullptr, QWidget* target = nullptr, const QString& text = "");

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* ev) override;

private:
    QString text;
};

#endif