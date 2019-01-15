#include "servericonwidget.hpp"
#include "QDebug"
#include "QPainter"
#include "discord/client.hpp"

ServerIconWidget::ServerIconWidget(QWidget* parent) : ServerIconWidget(nullptr, discord::Guild{}, parent) {}

ServerIconWidget::ServerIconWidget(discord::Client* client, discord::Guild const& guild, QWidget* parent)
    : QWidget(parent), name(QString::fromStdString(guild.name)) {
    auto iconData = client->get_guild_icon(guild, 128);

    qDebug() << iconData.data.data();

    if (icon.loadFromData(iconData.data.data(), "PNG")) {
        qDebug() << "loaded icon";
    }
}

QSize ServerIconWidget::sizeHint() const {
    return QSize{40, 40};
}

void ServerIconWidget::paintEvent(QPaintEvent* event) {
    QPainter painter{this};

    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawPixmap(rect(), icon);
}
