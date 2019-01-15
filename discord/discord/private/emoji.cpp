#include "classes/emoji.hpp"
#include "nlohmann/json.hpp"
#include "utils/json.hpp"

namespace discord {
    Emoji Emoji::from_json(nlohmann::json const& json) {
        Emoji emoji = json;
        return emoji;
    }

    void from_json(nlohmann::json const& json, Emoji& emoji) {
        json.at("name").get_to(emoji.name);

        json::utils::get_nullable_optional_field(json, "id", emoji.id);

        // json::utils::get_optional_field(json, "roles", emoji.roles);
        json::utils::get_optional_field(json, "user", emoji.user);
        json::utils::get_optional_field(json, "animated", emoji.animated);
        json::utils::get_optional_field(json, "managed", emoji.managed);
        json::utils::get_optional_field(json, "require_colons", emoji.require_colons);
    }
} // namespace discord