#ifndef DISCORD_AUTH_HPP
#define DISCORD_AUTH_HPP

#include "rpp/string.hpp"
#include "types.hpp"

namespace discord {
    namespace auth {
        String login(String const& email, String const& password);
    } // namespace auth
} // namespace discord

#endif // !DISCORD_AUTH_HPP
