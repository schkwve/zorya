cmake_minimum_required(VERSION 3.26)

#### PROJECT INFO ####

# Description
set(PROJECT_DESCRIPTION "A very nice web browser")

# Version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# Website
set(WEBSITE https://sovyetskisoyouzy.github.io)

######################

project(SovyetskiSoyouzy
	VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	DESCRIPTION ${PROJECT_DESCRIPTION}
  HOMEPAGE_URL ${WEBSITE}
	LANGUAGES C CXX)

# Set basic properties
set(EXECUTABLE_NAME SusieBrowser)
set(PROJECT_NAME "Sovyetski Soyouzy")

# Make sure every prerequisite is installed
find_package(OpenSSL REQUIRED)

# Includesssss
include_directories(src)
include_directories(${OPENSSL_INCLUDE_DIRS})

# Sources... Sources everywhere!
file(GLOB_RECURSE SRC src/*.c)

# If CMAKE_BUILD_TYPE is not specified, default to Debug build
if (NOT CMAKE_BUILD_TYPE)
  message(WARNING "CMAKE_BUILD_TYPE not set, defaulting to DEBUG...")
  set(CMAKE_BUILD_TYPE DEBUG)

  if (ENABLE_TRACE_LOGGING STREQUAL 1)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DENABLE_TRACE_LOGGING=1")
  endif()
endif()

# Set up build type flags
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
if (build_type STREQUAL debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__DEBUG -g3 -fsanitize=address")
elseif (build_type STREQUAL release)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
else ()
  message(FATAL_ERROR "Unknown build type specified in CMAKE_BUILD_TYPE!")
endif()

# .. And normal flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
endif()

# Compile
add_executable(${EXECUTABLE_NAME} ${SRC})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC OpenSSL::SSL)
