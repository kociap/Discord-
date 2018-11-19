#include "cache.hpp"

#include <fstream>
#include <filesystem>

namespace discord {
    void Cache::write_cache(std::filesystem::path const& path) const {
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directory(path.parent_path());
        }

        std::ofstream cache_file(path);
        cache_file << gateway << " " << access_token << " " << refresh_token << " "
                   << " " << token_type << " " << expires;
        cache_file.close();
    }

    void Cache::read_cache(std::filesystem::path const& path) {
        std::ifstream cache_file(path);
        cache_file >> gateway >> access_token >> refresh_token >> token_type >> expires;
    }
} // namespace discord
