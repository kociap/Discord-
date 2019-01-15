#include "classes/guild.hpp"

#include "utils/json.hpp"

namespace discord {
    Guild Guild::from_json(nlohmann::json const& json) {
        Guild guild = json;
        return guild;
    }

    void from_json(nlohmann::json const& json, Guild& guild) {
        json.at("id").get_to(guild.id);
        json.at("name").get_to(guild.name);
        json.at("emojis").get_to(guild.emojis);

        json::utils::get_nullable_optional_field(json, "icon", guild.icon);
        json::utils::get_nullable_optional_field(json, "splash", guild.splash);
        json::utils::get_optional_field(json, "owner_id", guild.owner_id);
        json::utils::get_optional_field(json, "permissions", guild.permissions);
        json::utils::get_optional_field(json, "owner", guild.owner);
    }
} // namespace discord
