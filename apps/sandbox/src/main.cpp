#include "dd/vulkan/loader.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    try {
        const auto version = dd::vulkan::queryLoaderVersion();
        std::cout << "DD_Engine Sandbox\nVulkan loader "
                  << version.major << '.' << version.minor << '.' << version.patch << '\n';
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "DD_Engine Sandbox: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
