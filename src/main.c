/**
 * @file main.c
 * @author lolguy91 <retek1544@gmail.com>, KapPetrov
 * <xicreationsofficial@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <suzTK/window.h>
#include <core/browser.h>
#include <netwerk/connect.h>
#include <netwerk/http.h>
#include <utils/buffer.h>
#include <string.h>

#include "utils/logging.h"
#include "antiralsei/parse.h"
#include "antiralsei/handler.h"

#include "UI/homepage.h"

GLFWwindow* mainWindow;

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
