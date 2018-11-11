#include "client.hpp"

#include "auth.hpp"
#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"

namespace discord {
    Client::Client(rpp::String const& token) : token(token) {}
    Client::Client(rpp::String&& token) : token(std::move(token)) {}

    User Client::get_me() {
        rpp::Headers headers({{"Authorization", "Bearer " + token}});
        rpp::Request req;
        req.set_headers(headers);
        req.set_verbose(true);
        req.set_verify_ssl(false);
        rpp::Response res = req.get(url::me);
        nlohmann::json json = nlohmann::json::parse(res.text);
        return User::from_json(json);
    }

} // namespace discord
