cmake_minimum_required(VERSION 3.15)
project(SDL_Graph LANGUAGES CXX)

# Find SDL2 package
find_package(SDL2 REQUIRED)

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
)

# Create static library
add_library(SDL_Graph STATIC ${SOURCES})

# Link SDL2 to SDL_Graph
target_link_libraries(SDL_Graph PRIVATE ${SDL2_LIBRARIES})

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
