#include "client.hpp"

#include "opcodes.hpp"
#include "urls.hpp"

#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"
#include "websocketpp/connection.hpp"

#include <QDebug>

// Timer
namespace discord {
    Timer::Timer(Stop_Function const& stop) : stop(stop) {}

    void Timer::cancel() {
        stop();
    }
} // namespace discord

// Client
namespace discord {
    Client::Client(String const& token) : gateway(), token(token) {}
    Client::Client(String&& token) : gateway(), token(std::move(token)) {}

    Client::~Client() {
        if (thread) {
            thread->join();
        }
    }

    User Client::get_me() {
        rpp::Headers headers({{"Authorization", token}});
        rpp::Request req;
        req.set_headers(headers);
        //        req.set_verbose(true);
        req.set_verify_ssl(false);
        rpp::Response res = req.get(url::me);
        nlohmann::json json = nlohmann::json::parse(res.text);
        return User::from_json(json);
    }

    Guilds Client::get_my_guilds() {
        rpp::Headers headers({{"Authorization", token}});
        rpp::Request req;
        req.set_headers(headers);
        //        req.set_verbose(true);
        req.set_verify_ssl(false);
        rpp::Response res = req.get(url::my_guilds);
        nlohmann::json json = nlohmann::json::parse(res.text);
        Guilds guilds = json;
        return guilds;
    }

    Channels Client::get_guild_channels(Snowflake const& guild_id) {
        rpp::Headers headers({{"Authorization", token}});
        rpp::Request req;
        req.set_headers(headers);
        //        req.set_verbose(true);
        req.set_verify_ssl(false);
        rpp::Response res = req.get(url::base + "/guilds/" + guild_id + "/channels");
        nlohmann::json json = nlohmann::json::parse(res.text);
        Channels channels = json;
        return channels;
    }

    void Client::send_message(Snowflake const& channel_id, String const& message) {
        rpp::Body body;
        body.append({{"content", message}});
        rpp::Headers headers({{"Authorization", token}});
        rpp::Request req;
        req.set_headers(headers);
        //        req.set_verbose(true);
        req.set_verify_ssl(false);
        rpp::Response res = req.post(url::base + "/channels/" + channel_id + "/messages", body);
    }

    void Client::connect(String const& url) {
        // Debug logging
        websocket.clear_access_channels(websocketpp::log::alevel::all);
        websocket.set_access_channels(websocketpp::log::alevel::connect);
        websocket.set_access_channels(websocketpp::log::alevel::disconnect);

        websocket.set_tls_init_handler([](websocketpp::connection_hdl) {
            return std::make_shared<websocketpp::lib::asio::ssl::context>(websocketpp::lib::asio::ssl::context::tlsv13_client);
        });

        websocket.init_asio();
        websocket.set_message_handler([this](websocketpp::connection_hdl handle, Websocket::message_ptr msg) -> void {
            websocket_message_handler(handle, msg); // force formatting
        });

        websocketpp::lib::error_code code;
        Websocket::connection_ptr connection = websocket.get_connection(url, code);
        if (code) {
            on_websocket_error(Websocket_Error::connection_failed, code.message());
            return;
        }

        handle = connection->get_handle();
        websocket.connect(connection);
        thread.reset(new std::thread([this]() { websocket.run(); }));
    }

    void Client::disconnect() {
        // TODO implement
        //        websocket.close()
    }

    void Client::websocket_message_handler(websocketpp::connection_hdl handle, Websocket::message_ptr msg) {
        nlohmann::json parsed_msg = nlohmann::json::parse(msg->get_payload());
        int opcode = parsed_msg.at("op");
        if (opcode == opcodes::gateway::hello) {
            heartbeat_interval = parsed_msg.at("d").at("heartbeat_interval");
            identify();
            heartbeat();

            qDebug() << "[opcode 10] Hello received from Discord\n" << QString::fromStdString(msg->get_payload()) << "\n";
        } else if (opcode == opcodes::gateway::heartbeat_ack) {
            heartbeat_ack = true;
            qDebug() << "[opcode 11] Ack received from Discord\n";
        } else {
            on_websocket_message(handle, msg);
        }
    }

    void Client::websocket_send(websocketpp::connection_hdl handle, String const& payload) {
        websocketpp::lib::error_code ec;
        websocket.send(handle, payload, websocketpp::frame::opcode::text, ec);
        // TODO add error handling
    }

    void Client::set_timer(uint32 time, std::function<void()> callback) {
        Websocket::timer_ptr timer = websocket.set_timer(time, [callback](websocketpp::lib::error_code const& code) {
            if (code == websocketpp::transport::error::operation_aborted) {
                return;
            }

            callback();
        });
    }

    void Client::identify() {
        websocket_send(handle, "{\"op\":2,\"d\":{\"token\":\"" + token + "\",\"properties\":{\"os\":\"Windows\"}}}");
    }

    void Client::heartbeat() {
        qDebug() << "heartbeat";
        if (!heartbeat_ack) {
            // TODO
            // No ack, terminate connection
        }

        websocket_send(handle, "{\"op\":1,\"d\":null}");
        set_timer(heartbeat_interval, [this]() { heartbeat(); });
    }

    // Discord events
    void Client::on_message() {}
    void Client::on_reaction() {}

    // Websocket events
    void Client::on_heartbeat() {
        qDebug() << "heartbeat";
    }
    void Client::on_connect() {}
    void Client::on_disconnect() {}
    void Client::on_websocket_error(Websocket_Error error, String const& message) {
        qDebug() << "websocket error: " << QString::fromStdString(message);
    }
    void Client::on_websocket_message(websocketpp::connection_hdl handle, websocketpp::connection<websocketpp::config::asio_tls_client>::message_ptr msg) {
        qDebug() << "Websocket message:" << QString::fromStdString(msg->get_payload());
    }

} // namespace discord
