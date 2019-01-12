#ifndef DISCORD_UTILS_JSON_HPP_INCLUDE
#define DISCORD_UTILS_JSON_HPP_INCLUDE

#include "nlohmann/json.hpp"
#include <optional>

namespace discord {
    namespace json {
        namespace utils {
            template <typename T>
            void get_nullable_optional_field(nlohmann::json const& json, char const* field_name, std::optional<T>& field) {
                if (json.count(field_name)) {
                    auto field_json = json.at(field_name);
                    if (field_json.is_null()) {
                        field = std::nullopt;
                    } else {
                        field = field_json.get<T>();
                    }
                }
            }

            template <typename T>
            void get_optional_field(nlohmann::json const& json, char const* field_name, std::optional<T>& field) {
                if (json.count(field_name)) {
                    field = json.at(field_name).get<T>();
                }
            }
        } // namespace utils
    }     // namespace json
} // namespace discord

#endif // !DISCORD_UTILS_JSON_HPP_INCLUDE