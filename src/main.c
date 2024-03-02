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

#include "utils/logging.h"
#include "html/parse.h"
#include "html/handler.h"

#include "UI/homepage.h"

GLFWwindow* mainWindow;

bool
browserInit()
{
    // dont't set icon ion MacOS
    #ifndef __APPLE__
        setIcon(mainWindow, "../res/logo.png", "../res/logo.png");
    #endif
    // Log OpenGL info
    log_info("Using OpenGL %s", glGetString(GL_VERSION));

    FILE* file = fopen("./res/test.html", "r");
    if (file == NULL) {
      log_error("Error opening file");
      return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* data = (char*)malloc(file_size + 1);
    if (data == NULL) {
      log_fatal("Memory allocation failed");
      fclose(file);
      return EXIT_FAILURE;
    }

    size_t bytes_read = fread(data, 1, file_size, file);
    if (bytes_read != file_size) {
      log_error("Error reading file");
      fclose(file);
      free(data);
      return EXIT_FAILURE;
    }

    data[file_size] = '\0';

    fclose(file);

    node_t* tree = parse_html(data, strlen(data));
    print_html_tree(tree, 0);
    handle_html(tree);

    free(data);
    free_html_tree(tree);

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
