#include "servericonwidget.hpp"
#include "QDebug"
#include "QFile"
#include "QPainter"
#include "discord/client.hpp"

ServerIconWidget::ServerIconWidget(QWidget* parent) : ServerIconWidget(nullptr, discord::Guild{}, parent) {}

ServerIconWidget::ServerIconWidget(discord::Client* client, discord::Guild const& guild, QWidget* parent)
    : QWidget(parent), name(QString::fromStdString(guild.name)) {
    auto iconData = client->get_guild_icon(guild, 128);
    QImage img;
    img.loadFromData(reinterpret_cast<const uchar*>(iconData.data.c_str()), static_cast<int>(iconData.data.size()));
    img.save(QString::fromStdString(guild.name) + ".png");
    icon = QPixmap::fromImage(img);
}

QSize ServerIconWidget::sizeHint() const {
    return QSize{40, 40};
}

void ServerIconWidget::paintEvent(QPaintEvent* event) {
    QPainter painter{this};

    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawPixmap(rect(), icon);
}
