#include "channel.hpp"

#include "utils/json.hpp"

namespace discord {
    Channel Channel::from_json(nlohmann::json const& json) {
        Channel channel = json;
        return channel;
    }

    void from_json(nlohmann::json const& json, Channel& channel) {
        json.at("id").get_to(channel.id);
        uint64_t type = json.at("type").get<uint64_t>();
        if (type == 0) {
            channel.type = Channel_Type::guild_text;
        } else if (type == 1) {
            channel.type = Channel_Type::dm;
        } else if (type == 2) {
            channel.type = Channel_Type::guild_voice;
        } else if (type == 3) {
            channel.type = Channel_Type::group_dm;
        } else {
            channel.type = Channel_Type::guild_category;
        }

        json::utils::get_optional_field(json, "recipients", channel.recipients);
        json::utils::get_optional_field(json, "owner_id", channel.owner_id);
        json::utils::get_optional_field(json, "guild_id", channel.guild_id);
        json::utils::get_optional_field(json, "name", channel.name);
        json::utils::get_optional_field(json, "position", channel.position);
        json::utils::get_optional_field(json, "nsfw", channel.nsfw);

        json::utils::get_nullable_optional_field(json, "parent_id", channel.parent_id);
        json::utils::get_nullable_optional_field(json, "icon", channel.icon);
        json::utils::get_nullable_optional_field(json, "topic", channel.topic);
    }
} // namespace discord
