#ifndef DISCORD_CLASSES_EMOJI_HPP_INCLUDE
#define DISCORD_CLASSES_EMOJI_HPP_INCLUDE

#include "types.hpp"
#include "user.hpp"
#include <vector>
#include <optional>

namespace discord {
    struct Emoji {
        std::string name;
		// nullable
        std::optional<Snowflake> id;
		// Roles that are allowed to use this emoji
		// std::optional<Roles> roles;
		// User who created this emoji
        std::optional<User> user;
        std::optional<bool> animated;
        std::optional<bool> managed;
        std::optional<bool> require_colons;

		Emoji from_json(nlohmann::json const&);
    };

    using Emojis = std::vector<Emoji>;

	// nlohmann::json specific function
	void from_json(nlohmann::json const&, Emoji&);
} // namespace discord

#endif // !DISCORD_CLASSES_EMOJI_HPP_INCLUDE