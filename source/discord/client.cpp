#include "client.hpp"

#include "opcodes.hpp"
#include "urls.hpp"

#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"
#include "websocketpp/connection.hpp"

#include <QDebug>
#include <fstream>
#include <map>

// Timer
namespace discord {
    Timer::Timer(Stop_Function const& stop) : stop(stop) {}

    void Timer::cancel() {
        stop();
    }
} // namespace discord

// Client
namespace discord {
    Client::Client(String const& token) : gateway(), token(token), heartbeat_timer([]() {}) {}
    Client::Client(String&& token) : gateway(), token(std::move(token)), heartbeat_timer([]() {}) {}

    Client::~Client() {}

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

    Relationships Client::get_relationships() {
        rpp::Headers headers({{"authorization", token}});
        rpp::Request req;
        req.set_headers(headers);
        req.set_verify_ssl(false);
        rpp::Response res = req.get(url::relationships);
        nlohmann::json json = nlohmann::json::parse(res.text);
        Relationships rels = json;
        return rels;
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
            websocket_message_handler(handle, msg); // force clang to format this line properly
        });

        websocketpp::lib::error_code code;
        Websocket::connection_ptr connection = websocket.get_connection(url, code);
        if (code) {
            on_websocket_error(Websocket_Error::connection_failed, code.message());
            // Let outside know it's not connected maybe?
            return;
        }

        handle = connection->get_handle();
        websocket.connect(connection);
        thread.reset(new std::thread([this]() { websocket.run(); }));
        on_connect();
    }

    void Client::disconnect(uint32 code, String const& reason) {
        heartbeat_timer.cancel();
        websocket.close(handle, code, reason);
        on_disconnect();
        if (thread) {
            thread->join();
        }
    }

    void Client::websocket_message_handler(websocketpp::connection_hdl handle, Websocket::message_ptr msg) {
        nlohmann::json parsed_msg = nlohmann::json::parse(msg->get_payload());
        int opcode = (parsed_msg.count("op") == 1 ? parsed_msg.at("op").get<int>() : -1);
        if (opcode == opcodes::gateway::hello) {
            heartbeat_interval = parsed_msg.at("d").at("heartbeat_interval").get<uint32>();
            identify();
            heartbeat();
        } else if (opcode == opcodes::gateway::heartbeat_ack) {
            heartbeat_ack = true;
        } else if (opcode == opcodes::gateway::dispatch) {
            String type = parsed_msg.at("t").get<String>();
            if (type == "READY") {
                on_ready(msg->get_payload());
            } else if (type == "PRESENCE_UPDATE") {
                qDebug() << QString::fromStdString(msg->get_payload());
            } else if (type == "TYPING_START") {
            } else if (type == "MESSAGE_CREATE") {
                qDebug() << QString::fromStdString(msg->get_payload());
                on_message(Message::from_json(parsed_msg.at("d")));
            }
        } else {
            // Unknown opcode
            on_websocket_message(handle, msg);
        }
    }

    void Client::websocket_send(websocketpp::connection_hdl handle, String const& payload) {
        websocketpp::lib::error_code ec;
        websocket.send(handle, payload, websocketpp::frame::opcode::text, ec);
        // TODO add error handling
    }

    Timer Client::set_timer(uint32 time, std::function<void()> callback) {
        Websocket::timer_ptr timer = websocket.set_timer(time, [callback](websocketpp::lib::error_code const& code) {
            if (code == websocketpp::transport::error::operation_aborted) {
                return;
            }

            callback();
        });

        return Timer([timer]() { timer->cancel(); });
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

        heartbeat_ack = false;
        websocket_send(handle, "{\"op\":1,\"d\":null}");
        on_heartbeat();
        heartbeat_timer = set_timer(heartbeat_interval, [this]() { heartbeat(); });
    }

    // Discord events
    void Client::on_message(Message const&) {}
    void Client::on_reaction() {}
    void Client::on_presence_update() {}

    // Websocket events
    void Client::on_heartbeat() {}
    void Client::on_connect() {}
    void Client::on_ready(String const&) {}
    void Client::on_disconnect() {}
    void Client::on_websocket_error(Websocket_Error error, String const& message) {
        qDebug() << "websocket error: " << QString::fromStdString(message);
    }
    void Client::on_websocket_message(websocketpp::connection_hdl handle, websocketpp::connection<websocketpp::config::asio_tls_client>::message_ptr msg) {
        qDebug() << "Websocket message:" << QString::fromStdString(msg->get_payload());
    }

} // namespace discord
