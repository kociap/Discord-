#include "user.hpp"

#include <string>

namespace discord {
    User User::from_json(nlohmann::json const& json) {
        User user = json;
        return user;
    }

    void from_json(nlohmann::json const& json, User& user) {
        // TODO assign all fields, not only 3...

        std::string str = json.at("id").get<std::string>();
        user.id = std::stoull(str);
        json.at("username").get_to(user.username);
        json.at("discriminator").get_to(user.discriminator);
    }
} // namespace discord
