#ifndef DISCORD_TYPES_HPP
#define DISCORD_TYPES_HPP

#include "rpp/string.hpp"

namespace discord {
    using int32 = int;
    using uint32 = unsigned int;
    using int64 = long long;
    using uint64 = unsigned long long;
    using String = rpp::String;
    // Unique id
    using Snowflake = String;
} // namespace discord

#endif // !DISCORD_TYPES_HPP
