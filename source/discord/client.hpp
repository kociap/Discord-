#ifndef DISCORD_CLIENT_HPP
#define DISCORD_CLIENT_HPP

#include "channel.hpp"
#include "data/usersettings.hpp"
#include "guild.hpp"
#include "image.hpp"
#include "message.hpp"
#include "relationship.hpp"
#include "types.hpp"
#include "user.hpp"

#ifdef _MSC_VER
// Disable all warnings from websocketpp and asio
#pragma warning(push, 0)
#endif // _MSC_VER

#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#define ASIO_STANDALONE
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_client.hpp"

#ifdef _MSC_VER
// Restore warnings
#pragma warning(pop)
#endif // _MSC_VER

#include <thread>
#include <vector>

namespace discord {
    class Timer {
    public:
        using Stop_Function = std::function<void()>;

        Timer(Stop_Function const&);
        void cancel();

    private:
        Stop_Function stop;
    };

    class Client {
    public:
        enum class Websocket_Error {
            connection_failed,
        };

        Client(String const& token);
        Client(String&& token);
        virtual ~Client();

        void connect(String const& url);
        void disconnect(uint32_t code, String const& reason);

        // Current user
        User get_me();
        Guilds get_guilds();
        Relationships get_relationships();

        Channels get_guild_channels(Snowflake const& guild_id);
        Image get_avatar(User const&);
        Image get_guild_icon(Guild const&);

        void send_message(Snowflake const& channel_id, String const& message);

        // Discord events
        virtual void on_message(Message const&);
        virtual void on_reaction();
        virtual void on_presence_update();

        // Websocket events
        virtual void on_heartbeat();
        virtual void on_connect();
        virtual void on_ready(User_settings const&, User const&, Relationships const&);
        virtual void on_disconnect();
        virtual void on_websocket_error(Websocket_Error error, String const& message);
        virtual void on_websocket_message(websocketpp::connection_hdl, websocketpp::connection<websocketpp::config::asio_tls_client>::message_ptr);

    protected:
        using Websocket = websocketpp::client<websocketpp::config::asio_tls_client>;
        Websocket websocket;

    private:
        String gateway;
        String token;
        std::shared_ptr<std::thread> thread = nullptr;
        websocketpp::connection_hdl handle;
        Timer heartbeat_timer;
        uint32_t heartbeat_interval = 0;
        bool heartbeat_ack = false;

        Timer set_timer(uint32_t time, std::function<void()> callback);
        void identify();
        void heartbeat();

        void websocket_message_handler(websocketpp::connection_hdl handle, Websocket::message_ptr msg);
        void websocket_send(websocketpp::connection_hdl handle, String const& payload);
    };
} // namespace discord

#endif // !DISCORD_CLIENT_HPP
