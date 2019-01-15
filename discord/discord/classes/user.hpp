#ifndef DISCORD_USER_HPP
#define DISCORD_USER_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"
#include <optional>
#include <vector>

namespace discord {
    // May be partial, only id is guaranteed to be filled (don't remember if that's true, actually)
    //
    // https://discordapp.com/developers/docs/resources/user#user-object-user-structure
    //
    // Undocumented fields:
    //    phone - unknown type, optional-nullable(?)
    struct User {
        Snowflake id;
        String username;
        String discriminator;
        // Avatar hash, nullable
        // If avatar begins with "a_", then it is available in GIF format
        // https://discordapp.com/developers/docs/reference#image-formatting
        std::optional<String> avatar;
        std::optional<String> locale;
        std::optional<String> email;
        uint64_t flags;
        std::optional<Nitro_Type> nitro_type;
        std::optional<bool> bot;
        std::optional<bool> mfa_enabled; // two factor authentication
        std::optional<bool> verified;

        static User from_json(nlohmann::json const&);
    };

    using Users = std::vector<User>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, User&);
} // namespace discord

#endif // !DISCORD_USER_HPP
