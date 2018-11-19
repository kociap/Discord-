#ifndef DISCORDPP_DISCORD_CLIENT_HPP
#define DISCORDPP_DISCORD_CLIENT_HPP

#include "discord/client.hpp"

class Discord_Client : public discord::Client {
public:
    using discord::Client::Client;

    // Discord events
    void on_message() override;

    // Websocket events
    void on_heartbeat() override;
    void on_connect() override;
    void on_disconnect() override;
};

#endif // !DISCORDPP_DISCORD_CLIENT_HPP
