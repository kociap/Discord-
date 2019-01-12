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
    };
} // namespace discord

#endif // !DISCORD_IMAGE_HPP
