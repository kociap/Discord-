#include "discordclient.hpp"

#include <QDebug>

// Discord events
void Discord_Client::on_message() {
    qDebug() << "message received";
}

// Websocket events
void Discord_Client::on_heartbeat() {
    qDebug() << "heartbeat";
}
void Discord_Client::on_connect() {
    qDebug() << "socket connected";
}
void Discord_Client::on_disconnect() {
    qDebug() << "socket disconnected";
}
