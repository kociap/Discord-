#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "discordclient.hpp"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    Discord_Client* client;
};

#endif // MAINWINDOW_H
