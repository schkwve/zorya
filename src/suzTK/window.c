/**
 * @file utils/logging.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief window management implementation
 */
#include "window.h"
#include <stb_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <utils/logging.h>

bool fullscreen = false;

/*
    @private
    @brief GLFW error callback

    @param error The error code
    @param description The error description
*/
static void
glfw_error_callback(int error, const char* description)
{
    log_error("GLFW Error %d: %s", error, description);
}

/*
    @private
    @brief GLFW resize callback

    @param window The window
    @param width The new width
    @param height The new height
*/
static void
glfw_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/*
    @brief Create a window

    @param width The width of the window
    @param height The height of the window
    @param title The title of the window

    @return A pointer to the created window
*/
GLFWwindow*
createWindow(int width, int height, const char* title)
{
    GLFWwindow* window;

    if (!fullscreen)
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    else
        window =
            glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
                             glfwGetVideoMode(glfwGetPrimaryMonitor())->height,
                             title,
                             glfwGetPrimaryMonitor(),
                             NULL);
    if (!window) {
        log_fatal("Failed to create GLFW window!");
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowUserPointer(window, NULL);
    glfwSetWindowSizeCallback(window, glfw_resize_callback);
    glfwSetErrorCallback(glfw_error_callback);

    // set minimum OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // line 69, nice
    return window;
}

/*
    @brief Destroy a window

    @param window The window to destroy
*/
void
destroyWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
}

/*
    @brief Swap buffers

    @param window The window to swap buffers
*/
void
finishFrame(GLFWwindow* window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/*
    @brief Set the title of a window

    @param window The window to set the title of
    @param title The new title
*/
void
setTitle(GLFWwindow* window, const char* title)
{
    glfwSetWindowTitle(window, title);
}
/*
    @brief Set the icon of a window

    @param window The window to set the icon of
    @param beegPath The path to the big icon
    @param smolPath The path to the small icon
*/

void
setIcon(GLFWwindow* window, char* beegPath, char* smolPath)
{
    GLFWimage image[2];

    stbi_set_flip_vertically_on_load(true);

    image[0].pixels =
        stbi_load(beegPath, &image[0].width, &image[0].height, NULL, 4);
    image[1].pixels =
        stbi_load(smolPath, &image[1].width, &image[1].height, NULL, 4);

    glfwSetWindowIcon(window, 1, (const GLFWimage*)&image);
}

/*
    @brief Enter fullscreen

    @param window The window to enter fullscreen for
*/
void
enterFullscreen(GLFWwindow* window)
{
    // I have no clue how to do this - lolguy91
    // But i do                      - KapPetrov
    fullscreen = true;
}
/*
    @brief Exit fullscreen

    @param window The window to exit fullscreen for
*/
void
exitFullscreen(GLFWwindow* window)
{
    // I have no clue how to do this - lolguy91
    // But i do                      - KapPetrov
    fullscreen = false;
}
