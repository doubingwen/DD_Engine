#pragma once

#include <cstdint>

namespace dd::vulkan {

struct LoaderVersion {
    std::uint32_t major;
    std::uint32_t minor;
    std::uint32_t patch;
};

[[nodiscard]] LoaderVersion queryLoaderVersion();

} // namespace dd::vulkan
