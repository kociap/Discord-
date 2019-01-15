#include "classes/message.hpp"

namespace discord {
    Message Message::from_json(nlohmann::json const& json) {
        Message msg = json;
        return msg;
    }

    void from_json(nlohmann::json const& json, Message& msg) {
        json.at("id").get_to(msg.id);
        json.at("content").get_to(msg.content);
        json.at("channel_id").get_to(msg.channel_id);
        json.at("author").get_to(msg.author);
        json.at("timestamp").get_to(msg.timestamp);
        if (json.count("guild_id")) {
            json.at("guild_id").get_to(msg.guild_id);
        }
    }
} // namespace discord
