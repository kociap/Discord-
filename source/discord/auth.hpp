#ifndef DISCORD_AUTH_HPP
#define DISCORD_AUTH_HPP

#include "authorizationdata.hpp"
#include "rpp/string.hpp"

#include <QString>

namespace discord {
    namespace auth {
        String login(String const& email, String const& password);
    } // namespace auth

    namespace url {
        QString const authorization("https://discordapp.com/api/oauth2/authorize");
        QString const token("https://discordapp.com/api/oauth2/token");
        QString const redirect("https://github.com/kociap/Discordpp");

        String const login("https://discordapp.com/api/v6/auth/login");
        String const base("https://discordapp.com/api");
        String const me("https://discordapp.com/api/users/@me");
        String const my_guilds("https://discordapp.com/api/users/@me/guilds");

        String const gateway("https://discordapp.com/api/gateway");
    } // namespace url
} // namespace discord

#endif // !DISCORD_AUTH_HPP
