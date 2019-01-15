#ifndef DISCORD_DATA_USERGUILDSETTINGS_HPP
#define DISCORD_DATA_USERGUILDSETTINGS_HPP

#include "../types.hpp"
#include <vector>

namespace discord {
	struct Channel_Overrides {
        Snowflake channel_id;
		// ???, possible values: 0, 1, 2, 3
        int32_t message_notifications;
		bool muted;
	};

    struct User_Guild_Settings {
        std::vector<Channel_Overrides> channel_overrides;
        Snowflake guild_id;
        // ???, possible values: 0, 1, 2, 3
        int32_t message_notifications;
		bool suppress_everyone;
        bool muted;
        bool mobile_push;
	};
} // namespace discord

#endif // !DISCORD_DATA_USERGUILDSETTINGS_HPP
