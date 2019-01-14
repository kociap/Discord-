#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include "QValidator"
#include "QWidget"
#include "discord/types.hpp"

class QLineEdit;

namespace Ui {
    class Login_window;
}

class Login_window : public QWidget {
    Q_OBJECT

public:
    explicit Login_window(QWidget* parent = nullptr);
    ~Login_window();

signals:
    void logged_in(discord::String const& token);
    void window_closed();

private slots:
    void on_login_button_clicked();

protected:
    void closeEvent(QCloseEvent*);

private:
    Ui::Login_window* ui;
};

#endif // LOGINWINDOW_HPP
