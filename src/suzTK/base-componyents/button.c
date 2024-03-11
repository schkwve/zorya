/**
 * @file suzTK/base-componyents/button.h
 * @author andrej123456789 <andrej.bartulinvr@gmail.com>
 * @date 05/03/2024
 * @brief button management implementation
 */

#include "button.h"

/**
 * @brief Creates a new button structure.
 *
 * @param window
 *        Window where button will be drawn        
 * 
 * @param x
 *        Starting position on x axis on the window
 *
 * @param y
 *        Starting position on y axis on the window
 *
 * @param width
 *        Width of the new button
 *
 * @param height
 *        Height of the new button
 * 
 * @param title
 *        Default title to set the button to
 * 
 * @param action
 *        Function pointer to function which will be performed when button is clicked
 *
 * @return Button pointer if it was created successfully;
 *         NULL otherwise.
 */
struct suztk_button *suzbutton_create_button(struct suztk_window* window, int x, int y, int width, int height, const char* title, void (*action)())
{
    struct suztk_button *new = 
        (struct suztk_button*)malloc(sizeof(struct suztk_button));

    new->window = window;
    new->rectangle = (SDL_Rect){x, y, width, height};

    new->title = malloc(sizeof(char) * strlen(title) + 1); /* strlen() doesn't count \0*/
    strcpy(new->title, title);

    new->action = action;
    return new;
}

/**
 * @brief Destroys a button object and sets it to NULL.
 *
 * @param button
 *        Button structure to be destroyed
 */
void suzbutton_destroy_button(struct suztk_button *button)
{
    free(button->title);
    free(button);
}

/**
 * @brief Renders a button object
 *
 * @param button
 *        Button structure to be rendered
 */
void suzbutton_render_button(struct suztk_button *button)
{
    if (button != NULL)
    {
        SDL_SetRenderDrawColor(button->window->renderer, 0, 255, 0, 0xFF);
        SDL_RenderFillRect(button->window->renderer, &button->rectangle);
    }
}

/**
 * @brief Updates the window's title with a new one
 *
 * @param button
 *        Button structure pointer
 *
 * @param title
 *        New button title
 */
void suzbutton_set_title(struct suztk_button *button, const char *title)
{
    if (button != NULL)
    {
        button->title = realloc(button->title, sizeof(char) * strlen(title) + 1);
        strcpy(button->title, title);
    }
}
