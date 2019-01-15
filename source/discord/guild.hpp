#ifndef DISCORD_GUILD_HPP
#define DISCORD_GUILD_HPP

#include "channel.hpp"
#include "nlohmann/json.hpp"
#include "types.hpp"
#include <optional>

namespace discord {
    // https://discordapp.com/developers/docs/resources/guild#guild-object
    //
    // Undocumented fields
    //    lazy - bool, nullable-optional
    struct Guild {
        Channels channels;
        Snowflake id;
        std::string name;
		// Optional, although documentation says otherwise
        std::optional<Snowflake> owner_id;
		// nullable-optional
        std::optional<Snowflake> afk_channel_id;
        // Guild icon hash, nullable
        std::optional<std::string> icon;
        // Guild splash hash, nullable
        // Wtf is that?!
        std::optional<std::string> splash;
        // ???
        std::optional<std::string> region;
		// ISO8601 timestamp
        // How do I store that?
        // std::optional<???> joined_at;
        std::optional<uint64_t> member_count;
        std::optional<uint64_t> permissions;
        std::optional<uint32_t> verification_level;
        // Two factor authentication
        std::optional<uint32_t> mfa_level;
        std::optional<uint32_t> explicit_content_filter;
        std::optional<uint32_t> default_message_notifications;
        std::optional<bool> owner;
        // ???
        std::optional<bool> lazy;
        // Is server considered large (???)
        std::optional<bool> large;

        static Guild from_json(nlohmann::json const&);
    };

    using Guilds = std::vector<Guild>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Guild&);
} // namespace discord

#endif // DISCORD_GUILD_HPP
