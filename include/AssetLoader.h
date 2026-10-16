#pragma once

#include <string>

class AssetLoader {
public:
    static std::string GetAssetPath(const char* relativePath);
};