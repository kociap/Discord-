#include "auth.hpp"
#include "urls.hpp"

#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>

namespace discord {
    namespace auth {
        std::variant<String, Login_error> login(String const& email, String const& password) {
            rpp::Body body("{\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"captcha_key\":null,\"undelete\":false}");
            rpp::Headers headers({{"Content-Type", String("application/json")}});
            rpp::Request req;
            req.set_headers(headers);
            req.set_verify_ssl(false); // Debug
            rpp::Response res = req.post(discord::url::login, body);
            nlohmann::json json = nlohmann::json::parse(res.text);
            using return_t = std::variant<String, Login_error>;
            if (res.status == 200) {
                return return_t(json.at("token").get<String>());
            } else if (json.count("password")) {
                return return_t(Login_error::incorrect_password);
            } else if (json.count("email")) {
                return return_t(Login_error::incorrect_email);
            } else if (json.count("captcha_key")) {
                return return_t(Login_error::captcha_required);
            } else {
                return return_t(Login_error::new_login_location);
            }
        }
    } // namespace auth
} // namespace discord
