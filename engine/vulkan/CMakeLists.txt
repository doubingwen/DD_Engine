find_package(Vulkan 1.3 REQUIRED)

add_library(dd_vulkan STATIC src/loader.cpp)
add_library(dd::vulkan ALIAS dd_vulkan)

target_compile_features(dd_vulkan PUBLIC cxx_std_20)
target_include_directories(dd_vulkan PUBLIC include)
target_link_libraries(dd_vulkan PRIVATE Vulkan::Vulkan)
