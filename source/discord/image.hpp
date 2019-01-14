#ifndef DISCORD_IMAGE_HPP
#define DISCORD_IMAGE_HPP

#include <string>

namespace discord {
    enum class Image_Format {
        png,
        gif,
        jpeg,
    };

    struct Image {
        std::string data;
        Image_Format format;
        uint32_t width = 0;
        uint32_t height = 0;
    };
} // namespace discord

#endif // !DISCORD_IMAGE_HPP
