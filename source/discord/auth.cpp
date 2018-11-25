#include "auth.hpp"
#include "urls.hpp"

#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>

namespace discord {
    namespace auth {
        String login(String const& email, String const& password) {
            rpp::Body body("{\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"captcha_key\":null,\"undelete\":false}");
            rpp::Headers headers({{"Content-Type", String("application/json")}});
            rpp::Request req;
            req.set_headers(headers);
            req.set_verify_ssl(false); // Debug
            rpp::Response res = req.post(discord::url::login, body);
            nlohmann::json json = nlohmann::json::parse(res.text);

            return json.at("token").get<String>();
        }
    } // namespace auth
} // namespace discord
