/**
 * @file suzTK/statemachine.h
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Pages file
 */

#include "statemachine.h"
#include "home.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>

page_t pages[] = {
    {"blank", NULL, NULL, NULL},
    {"home", initHomePage, renderHomePage, destroyHomePage},
    {"error", initErrorPage, renderErrorPage, destroyErrorPage},
};
size_t currentPageID = 0;
void* currentPagePrivatePointer = NULL;


void initStateMachine(){
    gotoPage("home");
}
void renderCurrentPage(){
    pages[currentPageID].render(currentPagePrivatePointer);
}
void destroyCurrentPage(){
    pages[currentPageID].destroy(currentPagePrivatePointer);
}

void gotoPage(char* pagename){
    for(int i = 0; i < sizeof(pages)/sizeof(pages[0]); i++){
        if(strcmp(pages[i].name, pagename) == 0){
            currentPageID = i;
            break;
        }
    }
    currentPagePrivatePointer = pages[currentPageID].init();
}