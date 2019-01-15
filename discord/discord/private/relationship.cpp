#include "classes/relationship.hpp"

namespace discord {
    Relationship_Type convert_to_enum(int type) {
        switch (type) {
        case 1:
            return Relationship_Type::friends;
        default:
            return Relationship_Type::friends;
        }
    }

    Relationship Relationship::from_json(nlohmann::json const& json) {
        Relationship relationship = json;
        return relationship;
    }

    void from_json(nlohmann::json const& json, Relationship& relationship) {
        // TODO assign all fields, not only 3...
        relationship.type = convert_to_enum(json.at("type").get<int>());
        json.at("user").at("id").get_to(relationship.id);
        json.at("user").at("username").get_to(relationship.username);
        json.at("user").at("discriminator").get_to(relationship.discriminator);
        //        json.at("user").at("avatar").get_to(relationship.avatar);
    }
} // namespace discord
