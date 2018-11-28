#ifndef DISCORD_URLS_HPP
#define DISCORD_URLS_HPP

#include "types.hpp"

namespace discord {
    namespace url {
        // POST
        String const login("https://discordapp.com/api/v6/auth/login");
        String const base("https://discordapp.com/api");
        // GET
        String const me("https://discordapp.com/api/users/@me");
        // GET
        String const my_guilds("https://discordapp.com/api/users/@me/guilds");
        // GET
        // Array of Relationship objects
        // [ { type, id, user { username, discriminator, id, avatar } } ]
        //
        // type:
        //     1 - friends
        String const relationships("https://discordapp.com/api/v6/users/@me/relationships");
        // GET
        String const gateway("https://discordapp.com/api/gateway");
    } // namespace url
} // namespace discord
#endif // !DISCORD_URLS_HPP
