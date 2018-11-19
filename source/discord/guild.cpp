#include "guild.hpp"

namespace discord {
    Guild Guild::from_json(nlohmann::json const& json) {
        Guild guild = json;
        return guild;
    }

    void from_json(nlohmann::json const& json, Guild& guild) {
        json.at("id").get_to(guild.id);
        json.at("name").get_to(guild.name);
        json.at("permissions").get_to(guild.permissions);
        json.at("owner").get_to(guild.owner);
    }
} // namespace discord
