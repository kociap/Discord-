#ifndef DISCORD_TYPES_HPP
#define DISCORD_TYPES_HPP

#include <vector>

namespace discord {
    using int32 = int;
    using uint32 = unsigned int;
    using int64 = long long;
    using uint64 = unsigned long long;
    using String = std::string;
    // Unique id
    using Snowflake = String;
    using Snowflakes = std::vector<Snowflake>;

    enum class Status {
        online,
        idle,
        do_not_disturb,
        offline,
        unchanged,
    };

    enum class Activity_Type {
        game,
        streaming,
        listening,
    };
} // namespace discord

#endif // !DISCORD_TYPES_HPP
