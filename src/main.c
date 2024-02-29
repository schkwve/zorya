/*
	main.c - Main application entry source code.
	Author of code written: KapPetrov
	History: Created on 2/29/2024
*/

#include <GL/glut.h> // Include Library GLUT

// Define window parameters
int WIDTH = 800;
int HEIGHT = 600;

const char* TITLE = "Sovyetski-soyouzy";

// Display function that gets called after window creation.
void display()
{
	// Clear the buffer bit
	glClear(GL_COLOR_BUFFER_BIT);
	
	glFlush(); // Flush
	// Swap buffers
	glutSwapBuffers();
}

// Main function
int main(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	// Initialize the display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// Window size is 800 by 600 for now.
	glutInitWindowSize(WIDTH, HEIGHT);
	// Window title
	glutCreateWindow(TITLE);
	// Setting the function that gets called after window creation.
	glutDisplayFunc(display);
	// Orthographic view
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	// Clear background color to white.
	glClearColor(1, 1, 1, 0);
	// This is the main loop
	glutMainLoop();
	// Return
	return 0;
}

