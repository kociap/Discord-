#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->listWidget->addItem(new QListWidgetItem("An0num0us"));
}

MainWindow::~MainWindow() {
    delete ui;
}
