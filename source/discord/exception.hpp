#ifndef DISCORD_EXCEPTION_HPP_INCLUDE
#define DISCORD_EXCEPTION_HPP_INCLUDE

#include <stdexcept>

namespace discord {
    class Http_Request_Failed : public std::runtime_error {
    public:
        int32_t status;
        std::string reason;

        Http_Request_Failed(int32_t status, std::string const& reason);
    };
} // namespace discord

#endif // !DISCORD_EXCEPTION_HPP_INCLUDE