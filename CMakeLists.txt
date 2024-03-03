cmake_minimum_required(VERSION 3.26)
project(SovietskiSoyouzy)

# Make sure every prerequisite is installed
find_package(SDL2 REQUIRED)

# Includesssss
include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS})

# Set debug variables
add_definitions("-D__DEBUG -g -fsanitize=address")


# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compile everything
file(GLOB_RECURSE SRC src/*.c)
add_executable(SusieBrowser ${SRC})
target_link_libraries(SusieBrowser PUBLIC ${SDL2_LIBRARIES} "-g -fsanitize=address")