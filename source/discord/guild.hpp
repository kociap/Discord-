#ifndef DISCORD_GUILD_HPP
#define DISCORD_GUILD_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct Guild {
        String name;
        Snowflake id;
        uint64 permissions;
        bool owner;

        static Guild from_json(nlohmann::json const&);
    };

    using Guilds = std::vector<Guild>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Guild&);
} // namespace discord

#endif // DISCORD_GUILD_HPP
