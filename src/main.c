/**
 * @file netwerk/connect.c
 * @author lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief Main file
 */

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <suzTK/window.h>

#include "utils/logging.h"

int main(void)
{
	/* Initialize GLFW */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* mainWindow = createWindow(640, 480, "Sovietski Soyuzy");

    // Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		log_fatal("Failed to initialize GLAD.");
		return -1;
	}

	setTitle(mainWindow, "TEST - Sovietski Soyuzy");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(mainWindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		/* finalize the frame */
		finishFrame(mainWindow);
	}

	glfwTerminate();
	return 0;
}