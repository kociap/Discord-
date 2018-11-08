#include "authorizationview.hpp"

#include "discord/apilinks.hpp"
#include "rpp/response.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>
#include <QUrlQuery>

AuthorizationView::AuthorizationView(QWidget *parent) : QWebEngineView(parent) {
    connect(this, &AuthorizationView::urlChanged, this, &AuthorizationView::onURLChanged);
}

void AuthorizationView::onURLChanged(QUrl const &url) {
    if (url.toString(QUrl::RemoveQuery) == discord::url::redirect) {
        QUrlQuery query(url);
        if (query.hasQueryItem("code")) {
            rpp::String code = query.queryItemValue("code").toStdString();
            rpp::Request req(discord::url::token.toStdString());
            rpp::Body body;
            body.add({rpp::BodyItem{"client_id", discord::auth::clientID.toStdString()},
                      rpp::BodyItem{"client_secret", discord::auth::clientSecret.toStdString()}, rpp::BodyItem{"grant_type", "authorization_code"},
                      rpp::BodyItem{"code", code}, rpp::BodyItem{"redirect_uri", discord::url::redirect.toStdString()},
                      rpp::BodyItem{"scope", discord::auth::scope.toStdString()}});

            rpp::Response res = req.post(body);
            qDebug() << "[" << res.status << "] " << QString::fromStdString(res.text);
        } else {
            // Handle errors
        }

        this->close();
    }
}
