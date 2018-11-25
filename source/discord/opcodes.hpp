#ifndef DISCORD_OPCODES_HPP
#define DISCORD_OPCODES_HPP

#include "types.hpp"

namespace discord {
    namespace opcodes {
        namespace gateway {
            constexpr int32 dispatch = 0;
            constexpr int32 heartbeat = 1;
            constexpr int32 identify = 2;
            constexpr int32 status_update = 3;
            constexpr int32 voice_state_update = 4;
            constexpr int32 resume = 6;
            constexpr int32 reconnect = 7;
            constexpr int32 request_guild_members = 8;
            constexpr int32 invalid_session = 9;
            constexpr int32 hello = 10;
            constexpr int32 heartbeat_ack = 11;
        } // namespace gateway

        namespace voice {
            constexpr int32 identify = 0;
            constexpr int32 hello = 9;
        } // namespace voice

    } // namespace opcodes
} // namespace discord

#endif // !DISCORD_OPCODES_HPP
