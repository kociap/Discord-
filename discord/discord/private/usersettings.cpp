#include "classes/usersettings.hpp"

namespace discord {
    void from_json(nlohmann::json const& json, User_Settings& settings) {
        json.at("guild_positions").get_to(settings.guild_positions);
        json.at("restricted_guilds").get_to(settings.restricted_guilds);
        json.at("theme").get_to(settings.theme);
        json.at("locale").get_to(settings.locale);
        json.at("timezone_offset").get_to(settings.timezone_offset);
        json.at("afk_timeout").get_to(settings.afk_timeout);
        json.at("explicit_content_filter").get_to(settings.explicit_content_filter);
        json.at("show_current_game").get_to(settings.show_current_game);
        json.at("render_reactions").get_to(settings.render_reactions);
        json.at("render_embeds").get_to(settings.render_embeds);
        json.at("message_display_compact").get_to(settings.message_display_compact);
        json.at("inline_embed_media").get_to(settings.inline_embed_media);
        json.at("inline_attachment_media").get_to(settings.inline_attachment_media);
        json.at("gif_auto_play").get_to(settings.gif_auto_play);
        json.at("enable_tts_command").get_to(settings.enable_tts_command);
        json.at("disable_games_tab").get_to(settings.disable_games_tab);
        json.at("developer_mode").get_to(settings.developer_mode);
        json.at("detect_platform_accounts").get_to(settings.detect_platform_accounts);
        json.at("default_guilds_restricted").get_to(settings.default_guilds_restricted);
        json.at("animate_emoji").get_to(settings.animate_emoji);
        json.at("convert_emoticons").get_to(settings.convert_emoticons);

        std::string status = json.at("status").get<std::string>();
        if (status == "online") {
            settings.status = Status::online;
        } else if (status == "dnd") {
            settings.status = Status::do_not_disturb;
        } else if (status == "idle") {
            settings.status = Status::idle;
        } else if (status == "invisible") {
            settings.status = Status::invisible;
        } else {
            settings.status = Status::offline;
        }
    }
} // namespace discord
