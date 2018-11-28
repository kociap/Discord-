#include "discordclient.hpp"

#include <QDebug>

void Discord_Client::on_message(discord::Message const& msg) {
    list->addItem(QString("Author: ") + QString::fromStdString(msg.author.username) + "\n" + QString::fromStdString(msg.content));
}
