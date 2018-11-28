#ifndef DISCORD_PRESENCE_HPP
#define DISCORD_PRESENCE_HPP

#include "activity.hpp"
#include "user.hpp"

namespace discord {
    struct Presence {
        User user;
        Activity game;
    };
} // namespace discord

#endif // !DISCORD_PRESENCE_HPP
