#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void findFile(const std::string& searchPath, const std::string& fileName, int startIndex, int step, std::string& result) {
    for (const auto& entry : fs::recursive_directory_iterator(searchPath)) {
        if (entry.is_regular_file() && entry.path().filename() == fileName) {
            result = entry.path().string();
            return;
        }
    }
}
