/**
 * @file suzTK/base-componyents/button.h
 * @author andrej123456789 <andrej.bartulinvr@gmail.com>
 * @date 05/03/2024
 * @brief button management implementation
 */

#include "button.h"

#include <utils/logging.h>

/**
 * @brief Checks if mouse position is inside a button
 * @param x
 *          mouse x
 * @param y
 *          mouse y
 * @param rect
 *          button
*/
bool mouse_inside_button(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < (rect.x + rect.w) && y >= rect.y && y < (rect.y + rect.h));
}

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
struct suztk_button *suzbutton_create_button(struct suztk_window *window, int x, int y, int width, int height, const char* title, void (*action)())
{
    struct suztk_button *new = 
        (struct suztk_button*)malloc(sizeof(struct suztk_button));

    new->window = window;
    new->rectangle = (SDL_Rect){x, y, width, height};

    new->surface = SDL_LoadBMP("../res/textures/button.bmp");
    new->texture = SDL_CreateTextureFromSurface(new->window->renderer, new->surface);
    SDL_FreeSurface(new->surface);

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
    if (button != NULL) {
        SDL_DestroyTexture(button->texture);
        
        free(button->title);
        free(button);

    } else {
        log_error("[suzbutton_destroy_button] Button is null!\n");
    }
}

/**
 * @brief Renders a button object
 *
 * @param window
 *        Window structure where button is located
 * 
 * @param button
 *        Button structure to be rendered
 */
void suzbutton_render_button(struct suztk_window *window, struct suztk_button *button)
{
    if (button != NULL) {
        /*SDL_SetRenderDrawColor(button->window->renderer, 0, 255, 0, 0xFF);
        SDL_RenderFillRect(button->window->renderer, &button->rectangle);*/

        SDL_RenderCopy(window->renderer, button->texture, NULL, &button->rectangle);

        int mouse_x, mouse_y;
        if (SDL_GetMouseState(&mouse_x, &mouse_y) == SDL_BUTTON_LEFT) {
            if (mouse_inside_button(mouse_x, mouse_y, button->rectangle)) {

                if (button->action != NULL) {
                    button->action();
                } else {
                    log_error("Function pointer is null!\n");
                }
            }
        }
    } else {
        log_error("[suzbutton_render_button] Button is null!\n");
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
    if (button != NULL) {
        button->title = realloc(button->title, sizeof(char) * strlen(title) + 1);
        strcpy(button->title, title);
    } else {
        log_error("[suzbutton_set_title] Button is null!\n");
    }
}
