#ifndef DISCORD_CHANNEL_HPP
#define DISCORD_CHANNEL_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct Channel {
        String id;

        static Channel from_json(nlohmann::json const&);
    };

    void from_json(nlohmann::json const&, Channel&);
} // namespace discord

#endif // !DISCORD_CHANNEL_HPP
