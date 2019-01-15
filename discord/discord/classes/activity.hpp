#ifndef DISCORD_ACTIVITY_HPP
#define DISCORD_ACTIVITY_HPP

#include "nlohmann/json.hpp"
#include "types.hpp"

namespace discord {
    struct Activity {
        String name;

        String url; // Stream url
        Activity_Type type;

        static Activity from_json(nlohmann::json const&);
    };

    using Activities = std::vector<Activity>;

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, Activity&);
} // namespace discord

#endif // !DISCORD_ACTIVITY_HPP
