/**
 * @file suzTK/statemachine.h
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Pages file
 */

#ifndef __UI_STATEMACHINE_H
#define __UI_STATEMACHINE_H

typedef struct page {
    char* name;
    void* (*init)();
    void (*render)(void* PP);
    void (*destroy)(void* PP);
} page_t;

void initStateMachine();
void renderCurrentPage();
void destroyCurrentPage();

void gotoPage(char* pagename);

#endif