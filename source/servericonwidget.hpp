#ifndef SERVERICONWIDGET_HPP
#define SERVERICONWIDGET_HPP

#include <QWidget>

class ServerIconWidget : public QWidget {
    Q_OBJECT
public:
    explicit ServerIconWidget(QWidget* parent = nullptr);
    ServerIconWidget(const QString& name, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void serverClicked();

public slots:

private:
    QString name;
};

#endif // SERVERICONWIDGET_HPP
