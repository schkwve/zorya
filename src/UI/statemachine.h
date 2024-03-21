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
    void (*init)(void *import_data);
    void (*render)();
    void (*destroy)();
};

void ui_statemachine_render_current_page();

void ui_statemachine_destroy_current_page();

void ui_statemachine_goto_page(char *pagename, void *import_data);

#endif /* UI_STATEMACHINE_H */
