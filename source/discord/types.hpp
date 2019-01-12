#ifndef DISCORD_TYPES_HPP
#define DISCORD_TYPES_HPP

#include <cstdint>
#include <vector>

namespace discord {
    using String = std::string;
    // Unique id
    using Snowflake = String;
    using Snowflakes = std::vector<Snowflake>;

    enum class Status {
        online,
        idle,
        do_not_disturb,
        invisible,
        offline,
        unchanged, // status udate event
    };

    enum class Activity_Type {
        game,
        streaming,
        listening,
    };

    //
    // https://discordapp.com/developers/docs/resources/user#user-object-user-flags
    namespace user_flags {
        constexpr uint64_t none = 0;
        constexpr uint64_t hypesquad_events = 1 << 2;
        constexpr uint64_t house_bravery = 1 << 6;
        constexpr uint64_t house_brilliance = 1 << 7;
        constexpr uint64_t house_balance = 1 << 8;
    }; // namespace user_flags

    //
    // https://discordapp.com/developers/docs/resources/user#user-object-premium-types
    enum class Nitro_Type {
        nitro,
        nitro_classic,
    };
} // namespace discord

#endif // !DISCORD_TYPES_HPP
