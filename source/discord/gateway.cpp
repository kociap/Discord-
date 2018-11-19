#include "gateway.hpp"

#include "auth.hpp"
#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"

namespace discord {
    namespace gateway {
        String get_gateway() {
            rpp::Request req;
            req.set_verbose(true);
            req.set_verify_ssl(false);
            rpp::Response res = req.get(url::gateway);
            nlohmann::json json = nlohmann::json::parse(res.text);
            return json.at("url").get<String>() + "/?v=6&encoding=json";
        }
    } // namespace gateway
} // namespace discord
