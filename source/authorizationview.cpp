#include "authorizationview.hpp"

#include "discord/auth.hpp"
#include "discord/client.hpp"
#include "discord/user.hpp"
#include "rpp/response.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>
#include <QUrlQuery>

Authorization_View::Authorization_View(QWidget* parent) : QWebEngineView(parent) {
    connect(this, &Authorization_View::urlChanged, this, &Authorization_View::on_url_changed);
}

void Authorization_View::on_url_changed(QUrl const& url) {
    if (url.toString(QUrl::RemoveQuery) == discord::url::redirect) {
        QUrlQuery query(url);
        if (query.hasQueryItem("code")) {
            rpp::String code = query.queryItemValue("code").toStdString();
            rpp::String token = discord::auth::exchange_code(code)["access_token"];
            discord::Client client(std::move(token));
            discord::User me = client.get_me();
            qDebug() << "[" << me.id << "] " << QString::fromStdString(me.username);
        } else {
            // Handle errors
        }

        close();
    }
}
