#include "mainwindow.hpp"
#include "QMetaObject"
#include "discord/auth.hpp"
#include "discord/gateway.hpp"
#include "discord/types.hpp"
#include "servericonwidget.hpp"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>

Main_window::Main_window(QWidget* parent) : QMainWindow(parent), ui(new Ui::Main_window), login_window(new Login_window()) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    login_window->show();

    connect(login_window, &Login_window::logged_in, this, &Main_window::logged_in);
    connect(login_window, &Login_window::window_closed, this, &Main_window::close);

    /*discord::String token = discord::auth::login("email", "password");
    discord::String gateway = discord::gateway::get_gateway();
    client = new Discord_Client(token);
    client->list = ui->listWidget;
    client->connect(gateway);
    discord::Relationships relationships = client->get_relationships();
    for (discord::Relationship const& relationship : relationships) {
        qDebug() << QString::fromStdString(relationship.username) << QString::fromStdString(relationship.id);
    }*/
}

Main_window::~Main_window() {
    delete ui;
    delete login_window;
    if (client != nullptr) {
        client->disconnect(1000, "log out");
        delete client;
    }
}

void Main_window::logged_in(discord::String const& token) {
    login_window->hide();
    show();
    client = new Discord_Client(token);
    discord::String gateway = discord::gateway::get_gateway();
    client->list = ui->listWidget;
    client->connect(gateway);

    auto servers = client->get_my_guilds();
    for (auto& server : servers) {
        new ServerIconWidget(QString::fromStdString(server.name), ui->listWidget);
    }
}
