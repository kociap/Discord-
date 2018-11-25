#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "discordclient.hpp"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

extern Discord_Client* client; // Terrible hack

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
