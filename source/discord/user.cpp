#include "user.hpp"

#include "utils/json.hpp"
#include <string>

namespace discord {
    User User::from_json(nlohmann::json const& json) {
        User user = json;
        return user;
    }

    void from_json(nlohmann::json const& json, User& user) {
        json.at("id").get_to(user.id);
        json.at("username").get_to(user.username);
        json.at("discriminator").get_to(user.discriminator);
        json::utils::get_nullable_optional_field(json, "avatar", user.avatar);
        json::utils::get_optional_field(json, "locale", user.locale);
        json::utils::get_optional_field(json, "email", user.email);
        json::utils::get_optional_field(json, "nitro_type", user.nitro_type);
        json::utils::get_optional_field(json, "bot", user.bot);
        json::utils::get_optional_field(json, "verified", user.verified);
        json::utils::get_optional_field(json, "mfa_enabled", user.mfa_enabled);
    }
} // namespace discord
