#ifndef DISCORD_CLIENT_HPP
#define DISCORD_CLIENT_HPP

#include "channel.hpp"
#include "guild.hpp"
#include "rpp/string.hpp"
#include "types.hpp"
#include "user.hpp"

#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#define ASIO_STANDALONE
#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_client.hpp"

#include <thread>
#include <vector>

namespace discord {
    using Channels = std::vector<Channel>;
    using Guilds = std::vector<Guild>;

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

        Client(String const& token, String const& refresh_token);
        Client(String&& token, String&& refresh_token);
        virtual ~Client();

        void connect(String const& url);
        void disconnect();

        // Current user
        User get_me();
        Guilds get_my_guilds();

        Channels get_guild_channels(Snowflake const& guild_id);

        void send_message(Snowflake const& channel_id, String const& message);

        // Discord events
        virtual void on_message();
        virtual void on_reaction();

        // Websocket events
        virtual void on_heartbeat();
        virtual void on_connect();
        virtual void on_disconnect();
        virtual void on_websocket_error(Websocket_Error error, String const& message);
        virtual void on_websocket_message(websocketpp::connection_hdl, websocketpp::connection<websocketpp::config::asio_tls_client>::message_ptr);

    protected:
        using Websocket = websocketpp::client<websocketpp::config::asio_tls_client>;
        Websocket websocket;

    private:
        String gateway;
        String token;
        String refresh_token;
        std::shared_ptr<std::thread> thread = nullptr;
        websocketpp::connection_hdl handle;
        uint32 heartbeat_interval = 0;

        void set_timer(uint32 time, std::function<void()> callback);
        void heartbeat();

        void websocket_message_handler(websocketpp::connection_hdl handle, Websocket::message_ptr msg);
        void websocket_send(websocketpp::connection_hdl handle, String const& payload);
    };
} // namespace discord

#endif // !DISCORD_CLIENT_HPP
