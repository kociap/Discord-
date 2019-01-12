#include "user.hpp"

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
        if (json.count("avatar")) {
            auto avatar_json = json.at("avatar");
            if (avatar_json.is_null()) {
                user.avatar = std::nullopt;
            } else {
                user.avatar = avatar_json.get<String>();
			}
        }
        if (json.count("locale")) {
            user.locale = json.at("locale").get<String>();
        }
        if (json.count("email")) {
            user.email = json.at("email").get<String>();
        }
        if (json.count("nitro_type")) {
            user.flags = json.at("nitro_type").get<uint64_t>();
        }
        if (json.count("bot")) {
            user.bot = json.at("bot").get<bool>();
        }
        if (json.count("verified")) {
            user.verified = json.at("verified").get<bool>();
        }
        if (json.count("mfa_enabled")) {
            user.mfa_enabled = json.at("mfa_enabled").get<bool>();
        }
    }
} // namespace discord
