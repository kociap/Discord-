#ifndef DISCORD_AUTH_HPP
#define DISCORD_AUTH_HPP

#include "rpp/string.hpp"
#include "types.hpp"
#include <variant>

namespace discord {
    namespace auth {
        enum class Login_error {
            captcha_required,
            incorrect_email,
            incorrect_password,
            new_login_location,
        };

        std::variant<String, Login_error> login(String const& email, String const& password);
    } // namespace auth
} // namespace discord

#endif // !DISCORD_AUTH_HPP
