#include "authorizationdata.hpp"

namespace discord {
    Authorization_Data Authorization_Data::from_json(nlohmann::json const& json) {
        Authorization_Data token = json;
        return token;
    }

    void from_json(nlohmann::json const& json, Authorization_Data& token) {
        json.at("access_token").get_to(token.access_token);
        json.at("refresh_token").get_to(token.refresh_token);
        json.at("scope").get_to(token.scope);
        json.at("token_type").get_to(token.token_type);
        json.at("expires_in").get_to(token.expires);
    }
} // namespace discord
