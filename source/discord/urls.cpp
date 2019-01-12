#include "urls.hpp"

namespace discord {
    namespace url {
        rpp::URL avatars(std::string const& user_id, std::string const& avatar_hash, std::string const& image_extension) {
            return "https://cdn.discordapp.com/avatars/" + user_id + "/" + avatar_hash + "." + image_extension;
        }

        rpp::URL default_avatars(std::string const& discriminator) {
            // User's discriminator must be modulo 5
            uint32_t discr_mod = std::stoi(discriminator) % 5;
            return "https://cdn.discordapp.com/embed/avatars/" + std::to_string(discr_mod) + ".png";
        }
    } // namespace url
} // namespace discord
