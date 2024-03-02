/**
 * @file main.c
 * @author lolguy91 <retek1544@gmail.com>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <stdbool.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <suzTK/window.h>

#include "utils/logging.h"

#include "UI/homepage.h"

GLFWwindow* mainWindow;

bool
browserInit()
{
    setTitle(mainWindow, "TEST - Sovietski Soyuzy");

    // Log OpenGL info
    log_info("Using OpenGL %s", glGetString(GL_VERSION));
    return true;
}
bool
browserUpdate()
{
    renderHomePage();

    // TODO: Update
    return true;
}
bool
browserDestroy()
{
    // TODO: Destroy
    return true;
}

int
main(void)
{
    /* Initialize GLFW */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    mainWindow = createWindow(640, 480, "Sovietski Soyuzy");

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log_fatal("Failed to initialize GLAD.");
        return -1;
    }

    if (!browserInit()) {
        log_fatal("Failed to initialize browser.");
        return -1;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mainWindow)) {
        if (!browserUpdate()) {
            break;
        }
        finishFrame(mainWindow);
    }
    browserDestroy();
    glfwTerminate();
    return 0;
}
