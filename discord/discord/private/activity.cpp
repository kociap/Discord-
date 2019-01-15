#include "classes/activity.hpp"

namespace discord {
    Activity Activity::from_json(nlohmann::json const& json) {
        Activity activity = json;
        return activity;
    }

    void from_json(nlohmann::json const&, Activity&) {}
} // namespace discord
