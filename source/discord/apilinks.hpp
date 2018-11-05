#ifndef DISCORD_APILINKS_HPP
#define DISCORD_APILINKS_HPP

#include <QString>

namespace discord {
    QString const clientID("505720390820167690");
    QString const clientSecret("Kw9ro2x46PtOUF2DpscyolxBL5SU_ySP");

    namespace url {
        QString const authorization("https://discordapp.com/api/oauth2/authorize");
        QString const token("https://discordapp.com/api/oauth2/token");
        QString const redirect("https://github.com/kociap/Discordpp");
    } // namespace url
} // namespace discord

#endif // !APILINKS_HPP
