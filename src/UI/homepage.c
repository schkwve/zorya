/**
 * @file suzTK/pages.c
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Pages file
 */

#include "homepage.h"

/*
    @brief Create Home Page
*/
void renderHomePage()
{
    // Clear the color to shade White.
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // Print the letter A (Not working as of now, just draws a line)
    printc('A');
}