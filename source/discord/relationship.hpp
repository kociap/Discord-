#ifndef DISCORD_RELATIONSHIP_HPP
#define DISCORD_RELATIONSHIP_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    enum class Relationship_Type {
        friends,
        blocked,
        pending_outgoing,
        pending_incoming,
    };

    struct Relationship {
        Snowflake id;
        String username;
        String discriminator;
        String avatar;
        Relationship_Type type;

        static Relationship from_json(nlohmann::json const&);
    };

    using Relationships = std::vector<Relationship>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Relationship&);
} // namespace discord

#endif // !DISCORD_RELATIONSHIP_HPP
