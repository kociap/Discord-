#include "loginwindow.hpp"
#include "ui_loginwindow.h"

#include "discord/auth.hpp"
#include <variant>

Login_window::Login_window(QWidget* parent) : QWidget(parent), ui(new Ui::Login_window) {
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
}

Login_window::~Login_window() {
    delete ui;
}

void Login_window::on_login_button_clicked() {
    bool valid = true;
    discord::String email(ui->email_edit->text().toStdString());
    discord::String password(ui->password_edit->text().toStdString());

    if (email.size() == 0) {
        ui->email_edit->setStyleSheet("border: 1px solid red;");
        valid = false;
    }

    if (password.size() == 0) {
        ui->password_edit->setStyleSheet("border: 1px solid red;");
        valid = false;
    }

    if (!valid) {
        return;
    }

    std::variant<discord::String, discord::auth::Login_error> login_result = discord::auth::login(email, password);
    if (std::holds_alternative<discord::String>(login_result)) {
        emit logged_in(std::get<discord::String>(login_result));
    } else {
        switch (std::get<discord::auth::Login_error>(login_result)) {
        case discord::auth::Login_error::captcha_required:
            break;
        case discord::auth::Login_error::incorrect_email:
            break;
        case discord::auth::Login_error::incorrect_password:
            break;
        case discord::auth::Login_error::new_login_location:
            break;
        }
    }
}

void Login_window::closeEvent(QCloseEvent* e) {
    QWidget::closeEvent(e);
    emit window_closed();
}
