#ifndef DISCORD_OPCODES_HPP
#define DISCORD_OPCODES_HPP

#include "types.hpp"

namespace discord {
    namespace opcodes {
        namespace gateway {
            constexpr int32_t dispatch = 0;
            constexpr int32_t heartbeat = 1;
            constexpr int32_t identify = 2;
            constexpr int32_t status_update = 3;
            constexpr int32_t voice_state_update = 4;
            constexpr int32_t resume = 6;
            constexpr int32_t reconnect = 7;
            constexpr int32_t request_guild_members = 8;
            constexpr int32_t invalid_session = 9;
            constexpr int32_t hello = 10;
            constexpr int32_t heartbeat_ack = 11;
        } // namespace gateway

        namespace voice {
            constexpr int32_t identify = 0;
            constexpr int32_t hello = 9;
        } // namespace voice

    } // namespace opcodes
} // namespace discord

#endif // !DISCORD_OPCODES_HPP
