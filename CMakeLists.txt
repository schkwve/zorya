cmake_minimum_required(VERSION 3.5)

project("Sovietski-Soyouzy")

#set(SRC src/main.c src/html/parse.c src/html/tree_utils.c)

file(GLOB SRC src/*.c src/**/*.c)

set(SRC ${SRC} lib/glad/src/glad.c)
add_subdirectory(lib/glfw)
include_directories(lib/glad/include)
include_directories(lib/glfw/include)
include_directories(lib/stb)
include_directories(src/)


if(APPLE)
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )
elseif(WIN32)
    list(APPEND EXTRA_LIBS
        "-lglu32 -lopengl32"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lX11"
    )
endif()

add_executable(SusieBrowser ${SRC})
target_link_libraries(SusieBrowser glfw ${EXTRA_LIBS})