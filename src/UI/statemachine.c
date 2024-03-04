/**
 * @file suzTK/statemachine.h
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Pages file
 */

#include <string.h>

#include "error.h"
#include "home.h"
#include "statemachine.h"

/**
 * @brief Array containing built-in pages and their callback functions.
 */
struct page pages[] = {
    { "blank", NULL, NULL, NULL },
    { "home", ui_homepage_init, ui_homepage_render, ui_homepage_destroy },
    { "error", ui_errorpage_init, ui_errorpage_render, ui_errorpage_destroy },
};

/**
 * @brief Current page index
 */
size_t currentPageID = 0;

/**
 * @brief ???
 */
void *currentPagePrivatePointer = NULL;

/**
 * @brief Initializes the UI state machine.
 */
void ui_statemachine_init()
{
    ui_statemachine_goto_page("home");
}

/**
 * @brief Calls renderer for the current page.
 */
void ui_statemachine_render_current_page()
{
    pages[currentPageID].render(currentPagePrivatePointer);
}

/**
 * @brief Destroys current page.
 */
void ui_statemachine_destroy_current_page()
{
    pages[currentPageID].destroy(currentPagePrivatePointer);
}

/**
 * @brief Goes to the current page.
 *
 * @param pagename
 *        Name of the page
 */
void ui_statemachine_goto_page(char *pagename)
{
    for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); i++) {
        if (strcmp(pages[i].name, pagename) == 0) {
            currentPageID = i;
            break;
        }
    }
    currentPagePrivatePointer = pages[currentPageID].init();
}