#ifndef DISCORD_CACHE_HPP
#define DISCORD_CACHE_HPP

#include "types.hpp"

#include <filesystem>

namespace discord {
    struct Cache {
        String gateway;
        String access_token;
        String refresh_token;
        String token_type;
        uint64 expires;

        void write_cache(std::filesystem::path const& path) const;
        void read_cache(std::filesystem::path const& path);
    };
} // namespace discord

#endif // !DISCORD_CACHE_HPP
