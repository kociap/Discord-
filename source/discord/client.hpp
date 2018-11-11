#ifndef DISCORD_CLIENT_HPP
#define DISCORD_CLIENT_HPP

#include "rpp/string.hpp"
#include "user.hpp"

namespace discord {
    class Client {
    public:
        Client(rpp::String const& token);
        Client(rpp::String&& token);

        User get_me();

    private:
        rpp::String token;
    };
} // namespace discord

#endif // !DISCORD_CLIENT_HPP
