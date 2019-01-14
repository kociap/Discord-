#ifndef DISCORD_DATA_USERSETTINGS_HPP
#define DISCORD_DATA_USERSETTINGS_HPP

#include "../types.hpp"
#include "nlohmann/json.hpp"

namespace discord {
    // Initial user settings received from READY event
    struct User_Settings {
		// Array of guilds' ids in the correct order
        std::vector<Snowflake> guild_positions;
        std::vector<Snowflake> restricted_guilds;
        String theme;
        String locale;
        Status status;
        int32_t timezone_offset;
        int32_t afk_timeout;
        int32_t explicit_content_filter;
        bool show_current_game;
        bool render_reactions;
        bool render_embeds;
        bool message_display_compact;
        bool inline_embed_media;
        bool inline_attachment_media;
        bool gif_auto_play;
        bool enable_tts_command;
        bool disable_games_tab;
        bool developer_mode;
        bool detect_platform_accounts;
        bool default_guilds_restricted;
        bool animate_emoji;
        bool convert_emoticons;
    };

    // nlohmann::json specific function
    void from_json(nlohmann::json const&, User_Settings&);
} // namespace discord

#endif // !DISCORD_DATA_USERSETTINGS_HPP
