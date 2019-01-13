#include "urls.hpp"

namespace discord {
    namespace url {
        rpp::URL avatar(std::string const& user_id, std::string const& avatar_hash, std::string const& image_extension) {
            return "https://cdn.discordapp.com/avatars/" + user_id + "/" + avatar_hash + "." + image_extension;
        }

        rpp::URL default_avatar(std::string const& discriminator) {
            // User's discriminator must be modulo 5
            uint32_t discr_mod = std::stoi(discriminator) % 5;
            return "https://cdn.discordapp.com/embed/avatars/" + std::to_string(discr_mod) + ".png";
        }

        rpp::URL guild_icon(std::string const& guild_id, std::string const& icon_hash, std::string const& image_extension) {
            return "https://cdn.discordapp.com/icons/" + guild_id + "/" + icon_hash + "." + image_extension;
        }

        rpp::URL create_dm(std::string const& user_id) {
            return "https://discordapp.com/api/users/" + user_id + "/channels";
        }
    } // namespace url
} // namespace discord
