#ifndef DISCORD_USER_HPP
#define DISCORD_USER_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct User {
        String id;
        String username;
        String discriminator;
        String avatar;
        String locale;
        String email;
        bool bot;
        bool mfa_enabled;
        bool verified;

        static User from_json(nlohmann::json const&);
    };

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, User&);
} // namespace discord

#endif // !DISCORD_USER_HPP
