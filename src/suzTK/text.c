/**
 * @file suzTK/text.c
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Text printing file
 */

#include "text.h"

/*
    @brief Print a character - Not working as of now
*/
void printc(char c)
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glFlush();
}