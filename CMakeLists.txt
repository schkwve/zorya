cmake_minimum_required(VERSION 3.26)
project(SovietskiSoyouzy)

# Include FindSDL2 packages
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Make sure every prerequisite is installed
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Includesssss
include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Set debug variables
add_definitions("-D__DEBUG")

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compile everything
file(GLOB_RECURSE SRC src/*.c)
add_executable(SusieBrowser ${SRC})
target_link_libraries(SusieBrowser PUBLIC SDL2::SDL2 SDL2::Image SDL2::TTF)
