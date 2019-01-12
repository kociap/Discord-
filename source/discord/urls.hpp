#ifndef DISCORD_URLS_HPP
#define DISCORD_URLS_HPP

#include "rpp/url.hpp"
#include "types.hpp"

namespace discord {
    namespace url {
        // TODO change type from String to URL

        // POST
        // Object with 3 optional fields
        // {
        //   email : [],
        //   password: [],
        //   captcha: []
        // }
        // Arrays contain error messages
        String const login("https://discordapp.com/api/auth/login");

        String const base("https://discordapp.com/api");

        // GET
        String const me("https://discordapp.com/api/users/@me");

        // GET
        String const my_guilds("https://discordapp.com/api/users/@me/guilds");

        // GET
        // Array of Relationship objects
        // [ { type, id, user { username, discriminator, id, avatar } } ]
        //
        // type:
        //     1 - friends
        String const relationships("https://discordapp.com/api/v6/users/@me/relationships");

        // GET
        String const gateway("https://discordapp.com/api/gateway");

        // GET
        // Avatar image endpoint
        // Supported file formats are: PNG, JPEG, GIF
        //
        // URL:
        //     https://cdn.discordapp.com/avatars/user_id/avatar_hash.image_extension
        //
        // Query params:
        //     size - size of the image, may be any power of 2 within [16, 2048]
        //
        // https://discordapp.com/developers/docs/reference#image-formatting-cdn-endpoints
        rpp::URL avatars(std::string const& user_id, std::string const& avatar_hash, std::string const& image_extension);

        // GET
        // Default avatar image endpoint
        // Supported file formats are: PNG
        //
        // URL:
        //     https://cdn.discordapp.com/embed/avatars/modified_discriminator.png
        //
        // Query params:
        //     size - size of the image, may be any power of 2 within [16, 2048]
        //
        // https://discordapp.com/developers/docs/reference#image-formatting-cdn-endpoints
        rpp::URL default_avatars(std::string const& discriminator);
    } // namespace url
} // namespace discord
#endif // !DISCORD_URLS_HPP
