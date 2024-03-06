/**
 * @file utils/logging.h
 * @author andrej123456789 <andrej.bartulinvr@gmail.com>, lolguy91 <retek1544@gmail.com>
 * @date 29/02/2024
 * @brief Utility for button management
 */

#ifndef SUZTK_BUTTON_H
#define SUZTK_BUTTON_H

#include <SDL.h>
#include <stdint.h>

#include "../window.h"

struct suztk_button {
    struct suztk_window* window;
    SDL_Rect rectangle;

    int x;
    int y;
    int width;
    int height;

    const char* title;
    void (*action)();
};

struct suztk_button *suzbutton_create_button(struct suztk_window* window, int x, int y, int width, int height, const char* title, void (*action)());
void suzbutton_destroy_button(struct suztk_button *button);
void suzbutton_render_button(struct suztk_button *button);

#endif
