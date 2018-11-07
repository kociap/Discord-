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
            QString code = query.queryItemValue("code");
            qDebug() << "Authorization successful! Code: " + code + "\n";

            QString headers("");
            QString requestData;
            requestData += "client_id=" + discord::auth::clientID;
            requestData += "&client_secret=" + discord::auth::clientSecret;
            requestData += "&grant_type=authorization_code";
            requestData += "&code=" + code;
            requestData += "&redirect_uri=" + discord::url::redirect;
            requestData += "&scope=" + discord::auth::scope;
            rpp::Response res = rpp::post(discord::url::token.toStdString(), headers.toStdString(), requestData.toStdString());
            qDebug() << "[" << res.status << "] " << QString::fromStdString(res.text);
        } else {
            // Handle errors
        }

        this->close();
    }
}
