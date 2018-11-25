#include "mainwindow.hpp"
#include "discord/auth.hpp"
#include "discord/gateway.hpp"
#include "discord/types.hpp"
#include "ui_mainwindow.h"
#include <algorithm>

#include <QDebug>

Discord_Client* client = nullptr;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    discord::String token = discord::auth::login("email", "password");
    discord::String gateway = discord::gateway::get_gateway();
    qDebug() << QString::fromStdString(gateway);
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    //            discord::Cache cache = {gateway, data.access_token, data.refresh_token, data.token_type,
    //                                    data.expires * 1000ULL + std::chrono::system_clock::to_time_t(now)};
    //            cache.write_cache("C:/data/cache.txt");
    client = new Discord_Client(token);
    client->connect(gateway);
    discord::User me = client->get_me();
    std::vector<discord::Guild> guilds = client->get_my_guilds();
    qDebug() << QString::fromStdString(me.id) << QString::fromStdString(me.username);
    for (discord::Guild const& guild : guilds) {
        qDebug() << QString::fromStdString(guild.id) << QString::fromStdString(guild.name);
    }
    discord::Channels discordpp_channels = client->get_guild_channels("");
    discord::Channel test =
        *std::find_if(discordpp_channels.begin(), discordpp_channels.end(), [](discord::Channel const& channel) { return channel.name == "test"; });
    client->send_message(test.id, "This message was sent via Discordpp");
}

MainWindow::~MainWindow() {
    delete ui;
    // TODO remove
    if (client != nullptr) {
        client->disconnect();
        delete client;
    }
}
