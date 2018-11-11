#include "auth.hpp"
#include "rpp/rpp.hpp"

#include <QDebug>

namespace discord {
    namespace auth {
        nlohmann::json exchange_code(rpp::String code) {
            rpp::Body body;
            body.add({rpp::Body_Item{"client_id", discord::auth::clientID.toStdString()},
                      rpp::Body_Item{"client_secret", discord::auth::clientSecret.toStdString()}, rpp::Body_Item{"grant_type", "authorization_code"},
                      rpp::Body_Item{"code", code}, rpp::Body_Item{"redirect_uri", discord::url::redirect.toStdString()},
                      rpp::Body_Item{"scope", discord::auth::scope.toStdString()}});
            rpp::Request req;
            // Discord's certificate cannot be identified (probably) because of a missing root certificate
            // Error: cannot validate local issuer certificate
            req.set_verify_ssl(false);
            req.set_verbose(true); // Debug
            rpp::Response res = req.post(discord::url::token.toStdString(), body);
            qDebug() << "[" << res.status << "] " << QString::fromStdString(res.text); // Debug

            return nlohmann::json::parse(res.text);
        }
    } // namespace auth
} // namespace discord
