/**
 * @file utils/logging.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief window management implementation
 */
#include "window.h"
#include <stdlib.h>
#include <utils/logging.h>

/*
    @brief Create a window

    @param width The width of the window
    @param height The height of the window
    @param title The title of the window

    @return A pointer to the created window
*/
GLFWwindow *createWindow(int width, int height, const char *title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        log_fatal("Failed to create GLFW window!");
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    return window;
}

/*
    @brief Destroy a window

    @param window The window to destroy
*/
void destroyWindow(GLFWwindow *window)
{
    glfwDestroyWindow(window);
}

/*
    @brief Swap buffers

    @param window The window to swap buffers
*/
void finishFrame(GLFWwindow *window)
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/*
    @brief Set the title of a window

    @param window The window to set the title of
    @param title The new title
*/
void setTitle(GLFWwindow *window, const char *title)
{
    glfwSetWindowTitle(window, title);
}
