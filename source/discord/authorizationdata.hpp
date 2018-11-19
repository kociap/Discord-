#ifndef AUTHORIZATION_DATA_HPP
#define AUTHORIZATION_DATA_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct Authorization_Data {
        String access_token;
        String refresh_token;
        String token_type;
        String scope;
        uint64 expires;

        static Authorization_Data from_json(nlohmann::json const&);
    };

    void from_json(nlohmann::json const&, Authorization_Data&);
} // namespace discord

#endif // !AUTHORIZATION_DATA_HPP
