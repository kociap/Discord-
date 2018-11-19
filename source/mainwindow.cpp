#include "mainwindow.hpp"
#include "authorizationview.hpp"
#include "discord/auth.hpp"
#include "ui_mainwindow.h"

Discord_Client* client = nullptr;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), authorization_view(parent) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    QString url(discord::url::authorization);
    // TODO add state to the request url
    url += "?scope=" + discord::auth::scope;
    url += "&response_type=code";
    url += "&redirect_uri" + discord::url::redirect;
    url += "&client_id=" + discord::auth::clientID;

    authorization_view.load(QUrl(url));
    authorization_view.show();
}

MainWindow::~MainWindow() {
    delete ui;
    // TODO remove
    if (client != nullptr) {
        client->disconnect();
        delete client;
    }
}
