#ifndef DISCORD_CHANNEL_HPP
#define DISCORD_CHANNEL_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"
#include "user.hpp"
#include <optional>

namespace discord {
	// https://discordapp.com/developers/docs/resources/channel#channel-object
    struct Channel {
        std::optional<Users> recipients;
        Snowflake id;
		// parent category of the channel, nullable
        std::optional<Snowflake> parent_id;
        std::optional<Snowflake> owner_id;
        std::optional<Snowflake> guild_id;
		// icon hash, nullable
        std::optional<std::string> icon;
		// May be null in the READY event
        std::optional<std::string> name;
		// nullable
        std::optional<std::string> topic;
		// sorting position
        std::optional<uint64_t> position;
        Channel_Type type;
        std::optional<bool> nsfw;

        static Channel from_json(nlohmann::json const&);
    };

    using Channels = std::vector<Channel>;

    void from_json(nlohmann::json const&, Channel&);
} // namespace discord

#endif // !DISCORD_CHANNEL_HPP
