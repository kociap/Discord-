#ifndef DISCORD_CHANNEL_HPP
#define DISCORD_CHANNEL_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct Channel {
        Snowflake id;
        String name;

        static Channel from_json(nlohmann::json const&);
    };

    using Channels = std::vector<Channel>;

    void from_json(nlohmann::json const&, Channel&);
} // namespace discord

#endif // !DISCORD_CHANNEL_HPP
