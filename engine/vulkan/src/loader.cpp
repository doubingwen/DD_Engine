#include "dd/vulkan/loader.hpp"

#include <vulkan/vulkan.h>

#include <stdexcept>
#include <string>

namespace dd::vulkan {

LoaderVersion queryLoaderVersion() {
    std::uint32_t version = 0;
    const VkResult result = vkEnumerateInstanceVersion(&version);
    if (result != VK_SUCCESS) {
        throw std::runtime_error(
            "vkEnumerateInstanceVersion failed with VkResult " + std::to_string(result));
    }

    return {
        VK_API_VERSION_MAJOR(version),
        VK_API_VERSION_MINOR(version),
        VK_API_VERSION_PATCH(version),
    };
}

} // namespace dd::vulkan
