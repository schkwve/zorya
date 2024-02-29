/**
 * @file utils/logging.h
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief Utility for window management
 */
#ifndef SUZTK_WINDOW_H
#define SUZTK_WINDOW_H
#include <GLFW/glfw3.h>

/*
    @brief Create a window

    @param width The width of the window
    @param height The height of the window
    @param title The title of the window

    @return A pointer to the created window
*/
GLFWwindow *createWindow(int width, int height, const char *title);
/*
    @brief Destroy a window

    @param window The window to destroy
*/
void destroyWindow(GLFWwindow *window);
/*
    @brief Swap the front and back buffers and poll for events

    @param window The window to finalize the frame for
*/
void finishFrame(GLFWwindow *window);
/*
    @brief Set the title of a window

    @param window The window to set the title of
    @param title The new title
*/
void setTitle(GLFWwindow *window, const char *title);

#endif