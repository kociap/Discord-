#ifndef SERVERICONWIDGET_HPP
#define SERVERICONWIDGET_HPP

#include "QPixmap"
#include "discord/classes/guild.hpp"
#include <QWidget>

namespace discord {
    class Client;
}

class ServerIconWidget : public QWidget {
    Q_OBJECT
public:
    explicit ServerIconWidget(QWidget* parent = nullptr);
    ServerIconWidget(discord::Client* client, discord::Guild const& guild, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void serverClicked();

public slots:

private:
    QString name;
    QPixmap icon;
};

#endif // SERVERICONWIDGET_HPP
