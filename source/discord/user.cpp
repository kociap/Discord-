#include "user.hpp"

#include <string>

namespace discord {
    User User::from_json(nlohmann::json const& json) {
        User user = json;
        return user;
    }

    void from_json(nlohmann::json const& json, User& user) {
        // TODO assign all fields, not only 3...
        json.at("id").get_to(user.id);
        json.at("username").get_to(user.username);
        json.at("discriminator").get_to(user.discriminator);
    }
} // namespace discord
