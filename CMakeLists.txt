cmake_minimum_required(VERSION 3.15)
project(SDL_Graph LANGUAGES CXX)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Include directories for the build process
include_directories(include Graphics ${SDL2_INCLUDE_DIRS})

# Compiler flags (optional: add SDL-specific flags if needed)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
set(SOURCES
    Graphics/Components/Template/RxComponent.cpp
    Graphics/RxFrame.cpp
    Graphics/DrawAbleSprite.hpp
    Graphics/Components/Label/RxLabel.cpp
)

# Create static library
add_library(SDL_Graph STATIC ${SOURCES})

# Link SDL2 to SDL_Graph
target_link_libraries(SDL_Graph PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Set output directory for the library to 'out' during build
set_target_properties(SDL_Graph PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out"
)

# Install library to system default lib folder (e.g., /usr/lib)
install(TARGETS SDL_Graph
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# Install header files from Graphics/ to system default include folder
install(DIRECTORY Graphics/
    DESTINATION include/SDL_Graph
    FILES_MATCHING
    PATTERN "*.hpp"
    PATTERN "*.h"
)

include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfig.cmake
    INSTALL_DESTINATION lib/cmake/SDL_Graph
    PATH_VARS CMAKE_INSTALL_PREFIX
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SDL_GraphConfig.cmake
    DESTINATION lib/cmake/SDL_Graph
)
