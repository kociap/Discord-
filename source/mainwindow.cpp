#include "mainwindow.hpp"
#include "authorizationview.hpp"
#include "discord/apilinks.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), authorizationView(parent) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    QString url(discord::url::authorization);
    // TODO add state to the request url
    url += "?scope=" + discord::auth::scope;
    url += "&response_type=code";
    url += "&redirect_uri" + discord::url::redirect;
    url += "&client_id=" + discord::auth::clientID;

    authorizationView.load(QUrl(url));
    authorizationView.show();
}

MainWindow::~MainWindow() {
    delete ui;
}
