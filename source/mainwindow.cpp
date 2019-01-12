#include "mainwindow.hpp"
#include "discord/auth.hpp"
#include "discord/gateway.hpp"
#include "discord/types.hpp"
#include "ui_mainwindow.h"
#include <algorithm>

#include "QMetaObject"
#include <QDebug>

Main_window::Main_window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Main_window), login_window(), guilds_list(this) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    login_window.show();

    connect(&login_window, &Login_window::logged_in, this, &Main_window::logged_in);
    connect(&login_window, &Login_window::window_closed, this, &Main_window::close);
}

Main_window::~Main_window() {
    delete ui;
    if (client != nullptr) {
        client->disconnect(1000, "log out");
        delete client;
    }
}

void Main_window::logged_in(discord::String const& token) {
    login_window.hide();
    show();
    client = new Discord_Client(token);
    discord::String gateway = discord::gateway::get_gateway();
    client->list = ui->listWidget;
    client->connect(gateway);
    discord::Guilds guilds = client->get_guilds();
    //for (discord::Guild const& guild : guilds) {
    //    guilds_list.add_guild(QString::fromStdString(guild.name));
    //}
    discord::User me = client->get_me();
    discord::Image my_avatar = client->get_avatar(me);
}
