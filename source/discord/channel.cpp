#include "channel.hpp"

namespace discord {
    Channel Channel::from_json(nlohmann::json const& json) {
        Channel channel = json;
        return channel;
    }

    void from_json(nlohmann::json const& json, Channel& channel) {
        json.at("id").get_to(channel.id);
    }
} // namespace discord
