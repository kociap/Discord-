#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "discordclient.hpp"
#include "loginwindow.hpp"
#include "widgets/guildslist.hpp"

#include <QMainWindow>

namespace Ui {
    class Main_window;
}

class Main_window : public QMainWindow {
    Q_OBJECT

public:
    explicit Main_window(QWidget* parent = nullptr);
    ~Main_window() override;

private slots:
    void logged_in(discord::String const& token);

private:
    Ui::Main_window* ui = nullptr;
    Login_window login_window;
    Discord_Client* client = nullptr;
    Guilds_list guilds_list;
};

#endif // !MAINWINDOW_HPP
