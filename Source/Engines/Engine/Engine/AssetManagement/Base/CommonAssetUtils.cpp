#include "CommonAssetUtils.h"

#include <filesystem>
#include <functional>

size_t GetIdFromPath(const char* aPath)
{
    std::filesystem::path path = std::filesystem::path(aPath).lexically_normal();
    return std::hash <std::string>{}(path.string());
}
