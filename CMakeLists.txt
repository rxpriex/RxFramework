cmake_minimum_required(VERSION 3.15)
project(SDL_Graph LANGUAGES CXX)

# Find SDL2 package
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

function(collect_sources ROOT_DIR OUT_VAR)
    file(GLOB_RECURSE SRC_C   "${ROOT_DIR}/*.cpp" "${ROOT_DIR}/*.cxx" "${ROOT_DIR}/*.c")
    set(SRCS ${SRC_C})
    set(${OUT_VAR} ${SRCS} PARENT_SCOPE)
endfunction()

collect_sources(${CMAKE_SOURCE_DIR}/src SOURCES)

# Create static library
add_library(SDL_Graph STATIC ${SOURCES})

# Set include directories (public so they are exported)
target_include_directories(SDL_Graph PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Graphics>
    $<INSTALL_INTERFACE:include/SDL_Graph>
    ${SDL2_INCLUDE_DIRS}
)

# Link dependencies (public so they are propagated)
target_link_libraries(SDL_Graph PUBLIC
    ${SDL2_LIBRARIES}
)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directory for the library to 'out' during build
set_target_properties(SDL_Graph PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
)

# Install library to system default lib folder
install(TARGETS SDL_Graph
    EXPORT SDL_GraphTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include/SDL_Graph
)

# Install header files from Graphics/ to include/SDL_Graph
install(DIRECTORY include/
    DESTINATION include/SDL_Graph
    FILES_MATCHING
    PATTERN "*.hpp"
    PATTERN "*.h"
)

# Generate and install config files
include(CMakePackageConfigHelpers)
set(PACKAGE_INCLUDE_INSTALL_DIR "include/SDL_Graph")
set(PACKAGE_LIB_INSTALL_DIR "lib")

# Configure the config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfig.cmake
    INSTALL_DESTINATION lib/cmake/SDL_Graph
    PATH_VARS CMAKE_INSTALL_PREFIX
)

# Generate version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfigVersion.cmake
    VERSION 1.0.0  # Adjust version as needed
    COMPATIBILITY SameMajorVersion
)

# Install config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfigVersion.cmake
    DESTINATION lib/cmake/SDL_Graph
)

# Export targets for build tree
export(TARGETS SDL_Graph
    FILE "${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphTargets.cmake"
)

# Install export set for install tree
install(EXPORT SDL_GraphTargets
    FILE SDL_GraphTargets.cmake
    DESTINATION lib/cmake/SDL_Graph
)
