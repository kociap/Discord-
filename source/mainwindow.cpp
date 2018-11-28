#include "mainwindow.hpp"
#include "discord/auth.hpp"
#include "discord/gateway.hpp"
#include "discord/types.hpp"
#include "ui_mainwindow.h"
#include <algorithm>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    discord::String token = discord::auth::login("email", "password");
    discord::String gateway = discord::gateway::get_gateway();
    client = new Discord_Client(token);
    client->list = ui->listWidget;
    client->connect(gateway);
    discord::Relationships relationships = client->get_relationships();
    for (discord::Relationship const& relationship : relationships) {
        qDebug() << QString::fromStdString(relationship.username) << QString::fromStdString(relationship.id);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    if (client != nullptr) {
        client->disconnect(1000, "log out");
        delete client;
    }
}
