#include "exception.hpp"

#include <string>

namespace discord {
    Http_Request_Failed::Http_Request_Failed(int32_t s, std::string const& r)
        : std::runtime_error("HTTP request failed with status " + std::to_string(status) + " " + reason), status(s), reason(r) {}
} // namespace discord