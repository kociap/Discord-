#ifndef DISCORD_APILINKS_HPP
#define DISCORD_APILINKS_HPP

#include <QString>

namespace discord {
    namespace auth {
        QString const clientID("505720390820167690");
        QString const clientSecret("Kw9ro2x46PtOUF2DpscyolxBL5SU_ySP");
        QString const scope("connections%20identify%20guilds%20guilds.join%20gdm.join%20messages.read%20rpc%20rpc.api%20rpc.notifications.read");
    } // namespace auth

    namespace url {
        QString const authorization("https://discordapp.com/api/oauth2/authorize");
        QString const token("https://discordapp.com/api/oauth2/token");
        QString const redirect("https://github.com/kociap/Discordpp");
    } // namespace url
} // namespace discord

#endif // !APILINKS_HPP
