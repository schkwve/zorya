/**
 * @file suzTK/statemachine.h
 * @author KapPetrov <xicreationsofficial@gmail.com>
 * @date 01/03/24
 * @brief Pages file
 */

#ifndef UI_STATEMACHINE_H
#define UI_STATEMACHINE_H

struct page
{
    char *name;
    void *(*init)();
    void (*render)(void *PP);
    void (*destroy)(void *PP);
};

void ui_statemachine_init();

void ui_statemachine_render_current_page();

void ui_statemachine_destroy_current_page();

void ui_statemachine_goto_page(char *pagename);

#endif /* UI_STATEMACHINE_H */
