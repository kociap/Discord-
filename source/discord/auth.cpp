#include "auth.hpp"

#include "nlohmann/json.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>

namespace discord {
    namespace auth {
        Authorization_Data exchange_code(rpp::String code) {
            rpp::Body body;
            body.append({{"client_id", discord::auth::clientID.toStdString()},
                         {"client_secret", discord::auth::clientSecret.toStdString()},
                         {"grant_type", "authorization_code"},
                         {"code", code},
                         {"redirect_uri", discord::url::redirect.toStdString()},
                         {"scope", discord::auth::scope.toStdString()}});
            rpp::Request req;
            // Discord's certificate cannot be identified (probably) because of a missing root certificate
            // Error: cannot validate local issuer certificate
            req.set_verify_ssl(false);
            //            req.set_verbose(true); // Debug
            rpp::Response res = req.post(discord::url::token.toStdString(), body);
            //            qDebug() << "[" << res.status << "] " << QString::fromStdString(res.text); // Debug
            nlohmann::json json = nlohmann::json::parse(res.text);
            return Authorization_Data::from_json(json);
        }
    } // namespace auth
} // namespace discord
