#ifndef DISCORDPP_DISCORD_CLIENT_HPP
#define DISCORDPP_DISCORD_CLIENT_HPP

#include "discord/client.hpp"
#include <QListWidget>

class Discord_Client : public discord::Client {
public:
    QListWidget* list;

    using discord::Client::Client;

    void on_message(discord::Message const&) override;
};

#endif // !DISCORDPP_DISCORD_CLIENT_HPP
