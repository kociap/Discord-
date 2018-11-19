#ifndef DISCORD_AUTH_HPP
#define DISCORD_AUTH_HPP

#include "authorizationdata.hpp"
#include "rpp/string.hpp"

#include <QString>

namespace discord {
    namespace auth {
        QString const clientID("505720390820167690");
        QString const clientSecret("Kw9ro2x46PtOUF2DpscyolxBL5SU_ySP");
        QString const scope("connections%20identify%20guilds%20guilds.join%20gdm.join%20messages.read%20rpc%20rpc.api%20rpc.notifications.read");

        Authorization_Data exchange_code(rpp::String code);
    } // namespace auth

    namespace url {
        QString const authorization("https://discordapp.com/api/oauth2/authorize");
        QString const token("https://discordapp.com/api/oauth2/token");
        QString const redirect("https://github.com/kociap/Discordpp");

        rpp::String const base("https://discordapp.com/api");
        rpp::String const me("https://discordapp.com/api/users/@me");
        rpp::String const my_guilds("https://discordapp.com/api/users/@me/guilds");

        rpp::String const gateway("https://discordapp.com/api/gateway");
    } // namespace url
} // namespace discord

#endif // !DISCORD_AUTH_HPP
