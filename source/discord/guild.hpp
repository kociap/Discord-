#ifndef DISCORD_GUILD_HPP
#define DISCORD_GUILD_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"
#include <optional>

namespace discord {
    // https://discordapp.com/developers/docs/resources/guild#guild-object
    struct Guild {
        Snowflake id;
        String name;
        std::optional<Snowflake> owner_id;
        // Guild icon hash, nullable
        std::optional<std::string> icon;
        // Guild splash hash, nullable
        std::optional<std::string> splash;
        std::optional<uint64_t> permissions;
        std::optional<bool> owner;

        static Guild from_json(nlohmann::json const&);
    };

    using Guilds = std::vector<Guild>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Guild&);
} // namespace discord

#endif // DISCORD_GUILD_HPP
