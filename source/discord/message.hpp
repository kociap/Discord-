#ifndef DISCORD_MESSAGE_HPP
#define DISCORD_MESSAGE_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"
#include "user.hpp"

namespace discord {
    struct Message {
        User author;
        Snowflake id;
        Snowflake channel_id;
        Snowflake guild_id;
        String content;
        String timestamp;

        static Message from_json(nlohmann::json const&);
    };

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Message&);
} // namespace discord

#endif // !DISCORD_MESSAGE_HPP
