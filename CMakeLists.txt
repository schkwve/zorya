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

project(SovietskiSoyouzy
	VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
	DESCRIPTION ${PROJECT_DESCRIPTION}
  HOMEPAGE_URL ${WEBSITE}
	LANGUAGES C CXX)

# Set executable name
set(EXECUTABLE_NAME SusieBrowser)

# Set project name
set(PROJECT_NAME "Sovietski Soyouzy")

# Include FindSDL2 packages
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Make sure every prerequisite is installed
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Freetype REQUIRED)
find_package(Fontconfig REQUIRED)
find_package(HarfBuzz REQUIRED)
find_package(Cairo REQUIRED)
find_package(GLIB REQUIRED)

# Includesssss
include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${Fontconfig_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${HarfBuzz_INCLUDE_DIRS} ${Cairo_INCLUDE_DIRS})

# Sources... Sources everywhere!
file(GLOB_RECURSE SRC src/*.c)

# If CMAKE_BUILD_TYPE is not specified, default to Release build
if (NOT CMAKE_BUILD_TYPE)
  message(WARNING "CMAKE_BUILD_TYPE not set, defaulting to DEBUG...")
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

# Set up build type flags
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
if (build_type STREQUAL debug)
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " -D__DEBUG -g3 -fsanitize=address")
elseif (build_type STREQUAL release)
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " -O3")
else ()
  message(FATAL_ERROR "Unknown build type specified in CMAKE_BUILD_TYPE!")
endif()

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
target_compile_options(${EXECUTABLE_NAME} PUBLIC ${Fontconfig_COMPILE_OPTIONS} ${HarfBuzz_COMPILE_OPTIONS} ${Cairo_COMPILE_OPTIONS})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL2::SDL2 SDL2::Image ${Fontconfig_LIBRARIES} Freetype::Freetype ${HarfBuzz_LIBRARIES} ${Cairo_LIBRARIES})

# CPack
install(DIRECTORY res DESTINATION ${CMAKE_BINARY_DIR}/install
                  PATTERN "res/install/" EXCLUDE)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Cool People")
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_HOMEPAGE_URL ${WEBSITE})
set(CPACK_PACKAGE_ICON "../res/logo.png")
set(CPACK_PACKAGE_CONTACT "")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_CHECKSUM SHA256)
#set(CPACK_RESOURCE_FILE_LICENSE "LICENSE.txt")
#set(CPACK_RESOURCE_FILE_WELCOME "../res/install/welcome.txt"

set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/pkg)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows") # Windows
  set(CPACK_GENERATOR NSIS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux") # Linux
  set(CPACK_GENERATOR ZIP)
  set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin") # macOS
  set(CPACK_GENERATOR Bundle)
  set(CPACK_BUNDLE_NAME ${CPACK_PACKAGE_NAME})
  set(CPACK_BUNDLE_ICON ${CPACK_PACKAGE_ICON})
  set(CPACK_BUNDLE_PLIST "../res/install/macos_bundle.plist")

  get_filename_component(SDL2_LIBFILE "${SDL2_LIBRARIES}" REALPATH)
  get_filename_component(SDL2_IMAGE_LIBFILE "${SDL2_IMAGE_LIBRARIES}" REALPATH)
  get_filename_component(SDL2_TTF_LIBFILE "${SDL2_TTF_LIBRARIES}" REALPATH)
  get_filename_component(FREETYPE_LIBFILE "${FREETYPE_LIBRARIES}" REALPATH)
  get_filename_component(HARFBUZZ_LIBFILE "${HarfBuzz_LIBRARIES}" REALPATH)
  get_filename_component(CAIRO_LIBFILE "${Cairo_LIBRARIES}" REALPATH)

  install(FILES ${SDL2_LIBFILE} DESTINATION "../Library" COMPONENT libraries)
  install(FILES ${SDL2_IMAGE_LIBFILE} DESTINATION "../Library" COMPONENT libraries)
  install(FILES ${FREETYPE_LIBFILE} DESTINATION "../Library" COMPONENT libraries)
  install(FILES ${HARFBUZZ_LIBFILE} DESTINATION "../Library" COMPONENT libraries)
  install(FILES ${CAIRO_LIBFILE} DESTINATION "../Library" COMPONENT libraries)

  install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION "../MacOS" COMPONENT applications)
else ()
  message(FATAL_ERROR "Unsupported OS!")
endif ()

include(CPack)
