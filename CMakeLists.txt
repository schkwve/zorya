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
find_package(SDL2_ttf REQUIRED)

# Includesssss
include_directories(src)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

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
  set(PACKAGE_NAME "${PROJECT_NAME} (Debug)")
elseif (build_type STREQUAL release)
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} " -O3")
  set(PACKAGE_NAME "${PROJECT_NAME}")
else ()
  message(FATAL_ERROR "Unknown build type specified in CMAKE_BUILD_TYPE!")
endif()

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compile
add_executable(${EXECUTABLE_NAME} ${SRC})
target_link_libraries(${EXECUTABLE_NAME} PUBLIC SDL2::SDL2 SDL2::Image SDL2::TTF)

# CPack
#set(CPACK_PACKAGE_NAME ${PACKAGE_NAME})
#set(CPACK_PACKAGE_VENDOR "Cool People")
#set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
#set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
#set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
#set(CPACK_PACKAGE_CONTACT "")
#set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
#
#if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows") # Windows
#  set(CPACK_NSIS_INSTALL_ROOT ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_PACKAGE_INSTALL_DIRECTORY})
#  set(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
#  set(CPACK_NSIS_PACKAGE_NAME ${PROJECT_NAME})
#
#  #set(CPACK_NSIS_MUI_ICON "../res/installer/win_install.ico")
#  #set(CPACK_NSIS_MUI_UNIICON "../res/installer/win_install.ico")
#  #set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "../res/installer/win_welcomefinish.bmp")
#  #set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "../res/installer/win_unwelcomefinish.bmp")
#elif ($(CMAKE_SYSTEM_NAME) STREQUAL "Linux") # Linux
#elif ($(CMAKE_SYSTEM_NAME) STREQUAL "Darwin") # macOS
#  set(CPACK_BUNDLE_NAME "Sovietski Soyouzy")
#  set(CPACK_BUNDLE_PLIST "../cmake/macos_bundle.plist")
#endif ()
#
#include(CPack)
