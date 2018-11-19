#include "authorizationview.hpp"

#include "discord/auth.hpp"
#include "discord/cache.hpp"
#include "discord/gateway.hpp"
#include "discord/user.hpp"
#include "discordclient.hpp"
#include "rpp/response.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>
#include <QUrlQuery>
#include <chrono>

extern Discord_Client* client;

Authorization_View::Authorization_View(QWidget* parent) : QWebEngineView(parent) {
    connect(this, &Authorization_View::urlChanged, this, &Authorization_View::on_url_changed);
}

void Authorization_View::on_url_changed(QUrl const& url) {
    if (url.toString(QUrl::RemoveQuery) == discord::url::redirect) {
        QUrlQuery query(url);
        if (query.hasQueryItem("code")) {
            rpp::String code = query.queryItemValue("code").toStdString();
            auto data = discord::auth::exchange_code(code);
            rpp::String gateway = discord::gateway::get_gateway();
            qDebug() << QString::fromStdString(gateway);
            auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
            //            discord::Cache cache = {gateway, data.access_token, data.refresh_token, data.token_type,
            //                                    data.expires * 1000ULL + std::chrono::system_clock::to_time_t(now)};
            //            cache.write_cache("C:/data/cache.txt");
            client = new Discord_Client(data.access_token, data.refresh_token);
            client->connect(gateway);
            discord::User me = client->get_me();
            std::vector<discord::Guild> guilds = client->get_my_guilds();
            qDebug() << QString::fromStdString(me.id) << QString::fromStdString(me.username);
            for (discord::Guild const& guild : guilds) {
                qDebug() << QString::fromStdString(guild.id) << QString::fromStdString(guild.name);
            }
        } else {
            // Handle errors
        }

        close();
    }
}
