#include "authorizationview.hpp"

#include "discord/apilinks.hpp"

#include <QDebug>
#include <QUrlQuery>

AuthorizationView::AuthorizationView(QWidget *parent) : QWebEngineView(parent) {
    connect(this, &AuthorizationView::urlChanged, this, &AuthorizationView::onURLChanged);
}

void AuthorizationView::onURLChanged(QUrl const &url) {
    if (url.toString(QUrl::RemoveQuery) == discord::url::redirect) {
        QUrlQuery query(url);
        if (!query.hasQueryItem("code")) {
            // handle errors
            return;
        }

        QString code = query.queryItemValue("code");
        qDebug() << "Authorization successful! Code: " + code + "\n";

        this->close();
    }
}
