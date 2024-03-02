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
#include <netwerk/connect.h>
#include <netwerk/http.h>
#include <utils/buffer.h>
#include <string.h>

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

    http_header_t *headers = malloc(sizeof(http_header_t)*2);
    headers[0].name = "User-Agent";
    headers[0].data = "USSR; Mozilla/4.0";

    headers[1].name = "Host";
    headers[1].data = "example.com";

    http_request_t req = {
      .method = "GET",
      .path = "/",
      .ver = HTTP_1_1,
      .headers = headers,
      .header_len = 2,
      .data_len = 0,
      .data = 0
    };
  
    buffer_t* result = http_gen_request(&req);
  
    struct net_connection* con = net_create_connection("example.com", 80);
    net_send_data(con, result);
  
    buffer_t* res = malloc(sizeof(buffer_t));
    memset(res, 0, sizeof(buffer_t));
    net_recv_data(con, &res);

    char* ptr = malloc(res->data_len + 1);
    memcpy(ptr, res->data_ptr, res->data_len);
    ptr[res->data_len] = '\0';

    ptr = strchr(ptr, '<');

    node_t* tree = parse_html(ptr, strlen(ptr));
    print_html_tree(tree, 0);
    handle_html(tree);

    //free(ptr);
    free_html_tree(tree);

    buffer_destroy(result);
    buffer_destroy(res);
    net_destroy_connection(con);
    free(headers);
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
